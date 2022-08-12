//
//  PluginProcessor.cpp
//  FilePlayback_SharedCode
//
//  created by yu2924 on 2022-08-12
//  (c) 2022 yu2924
//

#include "PluginProcessor.h"
#include "PluginEditor.h"

class FilePlaybackAudioProcessorImpl
    : public FilePlaybackAudioProcessor
	, public juce::AsyncUpdater
{
private:
	static constexpr int MinimumLength = 128;
	static constexpr double DefaultSamplerate = 44100;
	juce::SharedResourcePointer<SharedResource> mSharedResource;
	juce::CriticalSection mLock;
	std::unique_ptr<juce::AudioFormatReader> mReader;
	std::unique_ptr<juce::AudioFormatReaderSource> mReaderSource;
    std::unique_ptr<juce::ResamplingAudioSource> mResampler;
	juce::ListenerList<FilePlaybackAudioProcessor::Listener> mListeners;
	juce::AudioSampleBuffer mReadBuffer;
	struct RenderStatus { double samplerate; int buffersize; bool prepared; } mRenderStatus = { DefaultSamplerate, 0, false };
	juce::File mFile;
	double mSpeed = 1;
	float mGain = 1;
	TimeRange mLoopRangeT = {};
	juce::Range<juce::int64> mLoopRangeS = {};
	bool mLooping = false;
	bool mRunning = false;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilePlaybackAudioProcessorImpl)
public:
	FilePlaybackAudioProcessorImpl()
		: FilePlaybackAudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
	{
	}
	virtual ~FilePlaybackAudioProcessorImpl() override
	{
	}
	// --------------------------------------------------------------------------------
	// internals
	void rebuildGraph()
	{
		if(mResampler && mRenderStatus.prepared) mResampler->releaseResources();
		mReader.reset();
		mReaderSource.reset();
		mResampler.reset();
		mLoopRangeT = {};
		std::unique_ptr<juce::AudioFormatReader> reader;
		reader.reset(mSharedResource->audioFormatManager.createReaderFor(mFile));
		if(reader && (MinimumLength <= reader->lengthInSamples))
		{
			mReader.reset(reader.release());
			mReaderSource = std::make_unique<juce::AudioFormatReaderSource>(mReader.get(), false);
			mResampler = std::make_unique<juce::ResamplingAudioSource>(mReaderSource.get(), false, mReader->numChannels);
			double tlen = (0 < mReader->sampleRate) ? ((double)mReader->lengthInSamples / mReader->sampleRate) : 0;
			mLoopRangeT = { 0, tlen };
		}
		updateLoopRange();
		updateRender();
		if(mResampler && mRenderStatus.prepared) mResampler->prepareToPlay(mRenderStatus.buffersize, mRenderStatus.samplerate);
	}
	void updateLoopRange()
	{
		double fs = DefaultSamplerate;
		juce::int64 len = 0;
		if(mReader)
		{
			fs = mReader->sampleRate;
			len = mReader->lengthInSamples;
		}
		juce::int64 begin = std::max(0i64, (juce::int64)(mLoopRangeT.begin * fs));
		juce::int64 end = std::min(len, (juce::int64)(mLoopRangeT.end * fs));
		mLoopRangeS = { begin, end };
	}
	void updateRender()
	{
		if(mResampler)
		{
			mReadBuffer.setSize(mReader->numChannels, mRenderStatus.buffersize);
		}
		else mReadBuffer.setSize(0, 0);
		updateResampler();
	}
	void updateResampler()
	{
		if(mResampler)
		{
			mResampler->setResamplingRatio(mSpeed * mReader->sampleRate / mRenderStatus.samplerate);
		}
	}
	// --------------------------------------------------------------------------------
	// attributes
	virtual const juce::String getName() const override { return JucePlugin_Name; }
	virtual bool acceptsMidi() const override { return false; }
	virtual bool producesMidi() const override { return false; }
	virtual bool isMidiEffect() const override { return false; }
	virtual double getTailLengthSeconds() const override { return 0; }
	// --------------------------------------------------------------------------------
    // programs
	virtual int getNumPrograms() override { return 1; }
	virtual int getCurrentProgram() override { return 0; }
	virtual void setCurrentProgram(int) override {}
	virtual const juce::String getProgramName(int) override { return {}; }
    virtual void changeProgramName(int, const juce::String&) override {}
	// --------------------------------------------------------------------------------
    // editor
	juce::AudioProcessorEditor* createEditor() override { return FilePlaybackAudioProcessorEditor::createInstance(*this); }
	virtual bool hasEditor() const override { return true; }
	// --------------------------------------------------------------------------------
	// persistence
	static constexpr uint32_t PersistenceVersion = 0x00000002;
	virtual void getStateInformation(juce::MemoryBlock& mb) override
	{
		juce::MemoryOutputStream str(mb, true);
		str.writeInt(PersistenceVersion);
		str.writeString(mFile.getFullPathName());
		str.writeFloat(mGain);
		str.writeDouble(mSpeed);
		str.writeDouble(mLoopRangeT.begin);
		str.writeDouble(mLoopRangeT.end);
		str.writeBool(mLooping);
		str.writeBool(mRunning);
		str.writeDouble(getPlaybackTime());
	}
	virtual void setStateInformation(const void* p, int cb) override
	{
		juce::MemoryInputStream str(p, cb, false);
		if(str.readInt() == PersistenceVersion)
		{
			setFile(str.readString());
			setGain(str.readFloat());
			setSpeed(str.readDouble());
			setLoopRange({ str.readDouble(), str.readDouble() });
			setLooping(str.readBool());
			setRunning(str.readBool());
			setPlaybackTime(str.readDouble());
		}
	}
	// --------------------------------------------------------------------------------
    // process
	virtual bool isBusesLayoutSupported(const BusesLayout& layouts) const override
	{
        return 0 < layouts.getMainOutputChannels();
	}
	virtual void prepareToPlay(double fs, int lbuf) override
	{
		juce::ScopedLock sl(mLock);
		mRenderStatus = { fs, lbuf , true };
		updateRender();
		if(mResampler) mResampler->prepareToPlay(lbuf, fs);
	}
	virtual void releaseResources() override
	{
		juce::ScopedLock sl(mLock);
		if(mResampler) mResampler->releaseResources();
		mRenderStatus = { DefaultSamplerate, 0, false };
		updateRender();
	}
	virtual void processBlock(juce::AudioBuffer<float>& asb, juce::MidiBuffer&) override
	{
        juce::ScopedNoDenormals noDenormals;
		asb.clear();
		juce::ScopedTryLock sl(mLock);
		if(sl.isLocked() && mReader && mRunning)
		{
			bool loopvalid = mLooping && (MinimumLength <= mLoopRangeS.getLength());
			int cchdst = std::min(asb.getNumChannels(), getTotalNumOutputChannels());
			int ldst = asb.getNumSamples();
			int idst = 0; while(idst < ldst)
			{
				// read
				juce::int64 esrc = loopvalid ? std::min(mReader->lengthInSamples, mLoopRangeS.getEnd()) : mReader->lengthInSamples;
				juce::int64 isrc = mReaderSource->getNextReadPosition();
				if(loopvalid && (esrc <= isrc))
				{
					mReaderSource->setNextReadPosition(mLoopRangeS.getStart());
					isrc = mReaderSource->getNextReadPosition();
				}
				int lseg = (int)std::min((juce::int64)(ldst - idst), esrc - isrc);
				if(lseg <= 0) break;
				mResampler->getNextAudioBlock(juce::AudioSourceChannelInfo(&mReadBuffer, 0, lseg));
				// render
				int cchsrc = mReader->numChannels;
				for(int ichsrc = 0, ichdst = 0; ichsrc < cchsrc; ++ichsrc)
				{
					const float* psrc = mReadBuffer.getReadPointer(ichsrc);
					float* pdst = asb.getWritePointer(ichdst, idst);
					juce::FloatVectorOperations::addWithMultiply(pdst, psrc, mGain, lseg);
					++ichdst;
					if(cchdst <= ichdst) ichdst = 0;
				}
				idst += lseg;
			}
			if(!loopvalid && (mReader->lengthInSamples <= mReaderSource->getNextReadPosition())) triggerAsyncUpdate();
		}
		if(!mReader) triggerAsyncUpdate();
	}
	// --------------------------------------------------------------------------------
	// juce::AsyncUpdater
	virtual void handleAsyncUpdate() override
	{
		setRunning(false);
	}
	// --------------------------------------------------------------------------------
	// FilePlaybackAudioProcessor public APIs
	virtual SharedResource* getSharedResource() override
	{
		return mSharedResource;
	}
	virtual void addListener(FilePlaybackAudioProcessor::Listener* v) override
	{
		mListeners.add(v);
	}
	virtual void removeListener(FilePlaybackAudioProcessor::Listener* v) override
	{
		mListeners.remove(v);
	}
	virtual juce::var getProperty(FPPID pid) const override
	{
		switch(pid)
		{
			case FPPID::File: return mFile.getFullPathName();
			case FPPID::Speed: return mSpeed;
			case FPPID::Gain: return mGain;
			case FPPID::LoopRange: return mLoopRangeT.toVar();
			case FPPID::Looping: return mLooping;
			case FPPID::Running: return mRunning;
			case FPPID::PlaybackTime:
			{
				juce::ScopedLock sl(mLock);
				if(mReader && (0 < mReader->sampleRate)) return (double)mReaderSource->getNextReadPosition() / mReader->sampleRate;
				else return {};
			}
			default: return {};
		}
	}
	virtual bool setProperty(FPPID pid, const juce::var& v) override
	{
		bool r = false;
		switch(pid)
		{
			case FPPID::File:
			{
				juce::ScopedLock sl(mLock);
				mFile = v.toString();
				rebuildGraph();
				r = true;
				break;
			}
			case FPPID::Speed:
				mSpeed = juce::jlimit(0.5, 2.0, (double)v);
				updateResampler();
				break;
			case FPPID::Gain:
				mGain = juce::jlimit(0.0f, 10.0f, (float)v);
				break;
			case FPPID::LoopRange:
			{
				juce::ScopedLock sl(mLock);
				double tlen = (mReader && (0 < mReader->sampleRate)) ? ((double)mReader->lengthInSamples / mReader->sampleRate) : 0;
				TimeRange tr = TimeRange::fromVar(v);
				// case: only the 'begin' is modified
				if((mLoopRangeT.begin != tr.begin) && (mLoopRangeT.end == tr.end))
				{
					mLoopRangeT.begin = juce::jlimit(0.0, tlen, tr.begin);
					mLoopRangeT.end = juce::jlimit(mLoopRangeT.begin, tlen, mLoopRangeT.end);
				}
				// case: only the 'end' is modified
				else if((mLoopRangeT.begin == tr.begin) && (mLoopRangeT.end != tr.end))
				{
					mLoopRangeT.end = juce::jlimit(0.0, tlen, tr.end);
					mLoopRangeT.begin = juce::jlimit(0.0, mLoopRangeT.end, mLoopRangeT.begin);
				}
				// otherwise
				else
				{
					mLoopRangeT.begin = juce::jlimit(0.0, tlen, tr.begin);
					mLoopRangeT.end = juce::jlimit(mLoopRangeT.begin, tlen, tr.end);
				}
				updateLoopRange();
				r = true;
				break;
			}
			case FPPID::Looping:
				mLooping = v;
				r = true;
				break;
			case FPPID::Running:
			{
				juce::ScopedLock sl(mLock);
				mRunning = v;
				// rewind at end
				if(v && mReader && (mReader->lengthInSamples <= mReaderSource->getNextReadPosition()))
				{
					mReaderSource->setNextReadPosition(0);
				}
				r = true;
				break;
			}
			case FPPID::PlaybackTime:
			{
				juce::ScopedLock sl(mLock);
				if(mReader)
				{
					juce::int64 p = juce::jlimit(0i64, mReader->lengthInSamples, (juce::int64)((double)v * mReader->sampleRate));
					mReaderSource->setNextReadPosition(p);
					r = true;
				}
				break;
			}
			default:
				break;
		}
		if(r) mListeners.call(&FilePlaybackAudioProcessor::Listener::propertyDidChange, this, pid);
		return r;
	}
};

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FilePlaybackAudioProcessorImpl();
}
