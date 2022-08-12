//
//  WaveformView.h
//  FilePlayback_SharedCode
//
//  created by yu2924 on 2022-08-13
//  (c) 2022 yu2924
//

#pragma once

#include <JuceHeader.h>
#include "CommonTypes.h"

class WaveformView
	: public juce::Component
{
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformView)
protected:
	class Impl;
	Impl* impl;
public:
	std::function<void(double)> onChangeCursorTime;
	std::function<void(TimeRange)> onChangeLoopRange;
	WaveformView(juce::AudioFormatManager& afm, juce::AudioThumbnailCache& atc);
	virtual ~WaveformView() override;
	virtual void resized() override;
	virtual void paint(juce::Graphics& g) override;
	juce::File getFile() const;
	void setFile(const juce::File&);
	TimeRange getLoopRange() const;
	void setLoopRange(const TimeRange&);
	double getPlaybackTime() const;
	void setPlaybackTime(double);
};
