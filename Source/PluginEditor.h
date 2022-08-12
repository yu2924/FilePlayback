//
//  PluginEditor.h
//  FilePlayback_SharedCode
//
//  created by yu2924 on 2022-08-12
//  (c) 2022 yu2924
//

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class FilePlaybackAudioProcessorEditor
	: public juce::AudioProcessorEditor
{
protected:
	FilePlaybackAudioProcessorEditor(FilePlaybackAudioProcessor& p)
		: AudioProcessorEditor(p)
	{
	}
public:
	static FilePlaybackAudioProcessorEditor* createInstance(FilePlaybackAudioProcessor& p);
};
