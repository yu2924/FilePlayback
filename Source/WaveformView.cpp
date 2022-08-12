//
//  WaveformView.cpp
//  FilePlayback_SharedCode
//
//  created by yu2924 on 2022-08-13
//  (c) 2022 yu2924
//

#include <JuceHeader.h>
#include "WaveformView.h"

namespace WFVColours
{
	static const juce::Colour Border			{ 0xff505050 };
	static const juce::Colour Background		{ 0xff202020 };
	static const juce::Colour Ruler				{ 0xff404040 };
	static const juce::Colour LoopRangeCursor	{ 0xffffff00 };
	static const juce::Colour PlaybackTimeCursor{ 0xff0080ff };
	static const juce::Colour Waveform			{ 0x8000ffff };
}

class WaveformView::Impl
	: public juce::Component
	, public juce::ChangeListener
{
public:
	class RangeMarker
		: public juce::Component
	{
	public:
		juce::Colour mFillColour;
		enum class Style { Center, Left, Right } mStyle;
		std::function<void(const juce::MouseEvent&)> onDrag;
		RangeMarker()
			: mFillColour(juce::Colours::white)
			, mStyle(Style::Center)
		{
		}
		virtual juce::MouseCursor getMouseCursor() override
		{
			return juce::MouseCursor(juce::MouseCursor::StandardCursorType::DraggingHandCursor);
		}
		virtual void paint(juce::Graphics& g) override
		{
			juce::Rectangle<float> rc = getLocalBounds().toFloat();
			juce::Path path;
			juce::Colour clr;
			switch(mStyle)
			{
				case Style::Center:
					path.startNewSubPath(rc.getCentreX(), rc.getBottom());
					path.lineTo(rc.getTopLeft());
					path.lineTo(rc.getTopRight());
					break;
				case Style::Left:
					path.startNewSubPath(rc.getX(), rc.getY());
					path.lineTo(rc.getRight(), rc.getY());
					path.lineTo(rc.getX(), rc.getBottom());
					break;
				case Style::Right:
					path.startNewSubPath(rc.getRight(), rc.getY());
					path.lineTo(rc.getRight(), rc.getBottom());
					path.lineTo(rc.getX(), rc.getY());
					break;
				default: break;
			}
			path.closeSubPath();
			g.setColour(mFillColour);
			g.fillPath(path);
		}
		virtual void mouseDrag(const juce::MouseEvent& me) override
		{
			if(onDrag) onDrag(me);
		}
		juce::Colour getFillColour() const
		{
			return mFillColour;
		}
		void setFillColour(const juce::Colour& v)
		{
			mFillColour = v;
			repaint();
		}
		Style getStyle() const
		{
			return mStyle;
		}
		void setStyle(Style v)
		{
			mStyle = v;
		}
		int getAxchorX() const
		{
			switch(mStyle)
			{
				case Style::Center: return getX() + getWidth() / 2;
				case Style::Left: return getX();
				case Style::Right: return getRight();
				default: return 0;
			}
		}
		void setAnchorX(int x)
		{
			switch(mStyle)
			{
				case Style::Center: setTopLeftPosition(x - getWidth() / 2, 0); break;
				case Style::Left: setTopLeftPosition(x, 0); break;
				case Style::Right: setTopLeftPosition(x - getWidth(), 0); break;
				default: break;
			}
		}
	};
	class VertCursor
		: public juce::Component
	{
	public:
		juce::Colour mFillColour;
		VertCursor()
			: mFillColour(juce::Colours::white)
		{
			setInterceptsMouseClicks(false, false);
		}
		virtual void parentSizeChanged() override
		{
			setSize(1, getParentComponent()->getHeight());
		}
		virtual void paint(juce::Graphics& g) override
		{
			g.fillAll(mFillColour);
		}
		juce::Colour getFillColour() const
		{
			return mFillColour;
		}
		void setFillColour(const juce::Colour& v)
		{
			mFillColour = v;
			repaint();
		}
		int getAnchorX() const
		{
			return getX();
		}
		void setAnchorX(int x)
		{
			setTopLeftPosition(x, 0);
		}
	};
	// --------------------------------------------------------------------------------
	WaveformView* mOwner;
	juce::AudioThumbnail mAudioThumbnail;
	RangeMarker mLeftMarker, mRightMarker;
	VertCursor mLeftCursor, mRightCursor, mPlaybackTimeCursor;
	juce::File mFile;
	TimeRange mLoopRange = {};
	double mPlaybackTime = 0;
	enum { HorzMargin = 4, RulerHeight = 10, MarkerWidth = 10 };
	Impl(WaveformView* owner, juce::AudioFormatManager& afm, juce::AudioThumbnailCache& atc)
		: mOwner(owner)
		, mAudioThumbnail(64, afm, atc)
	{
		setOpaque(true);
		mAudioThumbnail.addChangeListener(this);
		mLeftMarker.setFillColour(WFVColours::LoopRangeCursor);
		mLeftMarker.setSize(MarkerWidth, RulerHeight);
		mLeftMarker.setStyle(RangeMarker::Style::Left);
		mLeftMarker.onDrag = [this](const juce::MouseEvent& me)
		{
			if(!mOwner->onChangeLoopRange) return;
			TimeRange tr = mLoopRange;
			tr.begin = px2t(getLocalPoint(me.eventComponent, me.getPosition()).x);
			mOwner->onChangeLoopRange(tr);
		};
		addAndMakeVisible(mLeftMarker);
		mLeftCursor.setFillColour(WFVColours::LoopRangeCursor);
		mLeftCursor.setSize(1, getHeight());
		addAndMakeVisible(mLeftCursor);
		mRightMarker.setFillColour(WFVColours::LoopRangeCursor);
		mRightMarker.setSize(MarkerWidth, RulerHeight);
		mRightMarker.setStyle(RangeMarker::Style::Right);
		mRightMarker.onDrag = [this](const juce::MouseEvent& me)
		{
			if(!mOwner->onChangeLoopRange) return;
			TimeRange tr = mLoopRange;
			tr.end = px2t(getLocalPoint(me.eventComponent, me.getPosition()).x);
			mOwner->onChangeLoopRange(tr);
		};
		addAndMakeVisible(mRightMarker);
		mRightCursor.setFillColour(WFVColours::LoopRangeCursor);
		mRightCursor.setSize(1, getHeight());
		addAndMakeVisible(mRightCursor);
		mPlaybackTimeCursor.setFillColour(WFVColours::PlaybackTimeCursor);
		mPlaybackTimeCursor.setSize(1, getHeight());
		addAndMakeVisible(mPlaybackTimeCursor);
	}
	virtual ~Impl() override
	{
		mAudioThumbnail.removeChangeListener(this);
	}
	int t2px(double t) const
	{
		int cx = getWidth() - HorzMargin * 2;
		if(cx <= 0) return 0;
		double tlen = mAudioThumbnail.getTotalLength();
		return HorzMargin + ((0 < tlen) ? juce::roundToInt((double)cx * t / tlen) : 0);
	}
	double px2t(int px) const
	{
		int cx = getWidth() - HorzMargin * 2;
		if(cx <= 0) return 0;
		double tlen = mAudioThumbnail.getTotalLength();
		return tlen * (double)(px - HorzMargin) / (double)cx;
	}
	void adjustLoopRange()
	{
		int xl = t2px(mLoopRange.begin);
		int xr = t2px(mLoopRange.end);
		mLeftMarker.setAnchorX(xl);
		mLeftCursor.setAnchorX(xl);
		mRightMarker.setAnchorX(xr);
		mRightCursor.setAnchorX(xr);
	}
	void adjustPlaybackTime()
	{
		int x = t2px(mPlaybackTime);
		mPlaybackTimeCursor.setAnchorX(x);
	}
	virtual void resized() override
	{
		adjustLoopRange();
		adjustPlaybackTime();
	}
	virtual void paint(juce::Graphics& g) override
	{
		juce::Rectangle<int> rcpaint = g.getClipBounds();
		if(rcpaint.isEmpty()) return;
		juce::Rectangle<int> rc = getLocalBounds();
		juce::Rectangle<int> rcr = rc.removeFromTop(RulerHeight);
		juce::Rectangle<int> rcc = rc;
		juce::Rectangle<int> rcw = rcc.reduced(HorzMargin, 0);
		g.setColour(WFVColours::Ruler);
		g.fillRect(rcr.getIntersection(rcpaint));
		g.setColour(WFVColours::Background);
		g.fillRect(rcc.getIntersection(rcpaint));
		if(0 < mAudioThumbnail.getNumChannels())
		{
			double tlen = mAudioThumbnail.getTotalLength();
			g.setColour(WFVColours::Waveform);
			mAudioThumbnail.drawChannels(g, rcw, 0, tlen, 1);
		}
	}
	virtual void mouseDown(const juce::MouseEvent& me) override
	{
		if(!mOwner->onChangeCursorTime) return;
		double tlen = mAudioThumbnail.getTotalLength();
		mOwner->onChangeCursorTime(tlen * (double)me.x / (double)getWidth());
	}
	virtual void mouseDrag(const juce::MouseEvent& me) override
	{
		if(!mOwner->onChangeCursorTime) return;
		double tlen = mAudioThumbnail.getTotalLength();
		mOwner->onChangeCursorTime(tlen * (double)me.x / (double)getWidth());
	}
	virtual void changeListenerCallback(juce::ChangeBroadcaster*) override
	{
		repaint();
	}
	juce::File getFile() const
	{
		return mFile;
	}
	void setFile(const juce::File& v)
	{
		mFile = v;
		mAudioThumbnail.setSource(new juce::FileInputSource(mFile, true));
		adjustLoopRange();
		adjustPlaybackTime();
	}
	TimeRange getLoopRange() const
	{
		return mLoopRange;
	}
	void setLoopRange(const TimeRange& v)
	{
		mLoopRange = v;
		adjustLoopRange();
	}
	double getPlaybackTime() const
	{
		return mPlaybackTime;
	}
	void setPlaybackTime(double v)
	{
		mPlaybackTime = v;
		adjustPlaybackTime();
	}
};

WaveformView::WaveformView(juce::AudioFormatManager& afm, juce::AudioThumbnailCache& atc) { setOpaque(true); impl = new Impl(this, afm, atc); addAndMakeVisible(impl); }
WaveformView::~WaveformView() { removeChildComponent(impl); delete impl; }
void WaveformView::resized() { impl->setBounds(getLocalBounds().reduced(1));}
void WaveformView::paint(juce::Graphics& g) { g.setColour(WFVColours::Border); g.drawRect(getLocalBounds(), 1); }
juce::File WaveformView::getFile() const { return impl->getFile(); }
void WaveformView::setFile(const juce::File&v) { impl->setFile(v); }
TimeRange WaveformView::getLoopRange() const { return impl->getLoopRange(); }
void WaveformView::setLoopRange(const TimeRange& v) { impl->setLoopRange(v); }
double WaveformView::getPlaybackTime() const { return impl->getPlaybackTime(); }
void WaveformView::setPlaybackTime(double v) { impl->setPlaybackTime(v); }
