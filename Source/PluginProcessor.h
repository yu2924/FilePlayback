//
//  PluginProcessor.h
//  FilePlayback_SharedCode
//
//  created by yu2924 on 2022-08-12
//  (c) 2022 yu2924
//

#pragma once

#include <JuceHeader.h>
#include "CommonTypes.h"

struct SharedResource
{
    juce::AudioFormatManager audioFormatManager;
    juce::AudioThumbnailCache audioThumbnailCache;
    SharedResource() : audioThumbnailCache(16)
    {
        audioFormatManager.registerBasicFormats();
        if(juce::LookAndFeel_V4* lf4 = dynamic_cast<juce::LookAndFeel_V4*>(&juce::LookAndFeel::getDefaultLookAndFeel()))
        {
            lf4->setColourScheme(juce::LookAndFeel_V4::getLightColourScheme());
        }
    }
};

enum class FPPID
{
    File,
    Speed,
    Gain,
    LoopRange,
    Looping,
    Running,
    PlaybackTime,
};

class FilePlaybackAudioProcessor
    : public juce::AudioProcessor
{
public:
    struct Listener
    {
        virtual ~Listener() {}
        virtual void propertyDidChange(FilePlaybackAudioProcessor*, FPPID pid) = 0;
    };
    FilePlaybackAudioProcessor(const BusesProperties& ioConfig) : AudioProcessor(ioConfig) {}
    virtual SharedResource* getSharedResource() = 0;
    virtual void addListener(Listener*) = 0;
    virtual void removeListener(Listener*) = 0;
    virtual juce::var getProperty(FPPID) const = 0;
    virtual bool setProperty(FPPID, const juce::var&) = 0;
    // binding
    juce::File getFile() const { return getProperty(FPPID::File).toString(); }
    bool setFile(const juce::File& v) { return setProperty(FPPID::File, v.getFullPathName()); }
    double getSpeed() const { return getProperty(FPPID::Speed); }
    bool setSpeed(double v) { return setProperty(FPPID::Speed, v); }
    float getGain() const { return getProperty(FPPID::Gain); }
    bool setGain(float v) { return setProperty(FPPID::Gain, v); }
    TimeRange getLoopRange() const { return TimeRange::fromVar(getProperty(FPPID::LoopRange)); }
    bool setLoopRange(const TimeRange& v) { return setProperty(FPPID::LoopRange, v.toVar()); }
    bool isLooping() const { return getProperty(FPPID::Looping); }
    bool setLooping(bool v) { return setProperty(FPPID::Looping, v); }
    bool isRunning() const { return getProperty(FPPID::Running); }
    bool setRunning(bool v) { return setProperty(FPPID::Running, v); }
    double getPlaybackTime() const { return getProperty(FPPID::PlaybackTime); }
    bool setPlaybackTime(double v) { return setProperty(FPPID::PlaybackTime, v); }
};
