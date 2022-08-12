//
//  PluginEditor.cpp
//  FilePlayback_SharedCode
//
//  created by yu2924 on 2022-08-12
//  (c) 2022 yu2924
//

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "EditorForm.h"

class FilePlaybackAudioProcessorEditorImpl
	: public FilePlaybackAudioProcessorEditor
{
private:
	FilePlaybackAudioProcessor& audioProcessor;
	EditorForm mEditorForm;
	juce::TooltipWindow mTooltipWindow;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilePlaybackAudioProcessorEditorImpl)
public:
	FilePlaybackAudioProcessorEditorImpl(FilePlaybackAudioProcessor& p)
		: FilePlaybackAudioProcessorEditor(p)
		, audioProcessor(p)
		, mEditorForm(&p)
	{
		addAndMakeVisible(mEditorForm);
		setSize(mEditorForm.getWidth(), mEditorForm.getHeight());
	}
	virtual ~FilePlaybackAudioProcessorEditorImpl() override
	{
	}
	virtual void resized() override
	{
		mEditorForm.setBounds(getLocalBounds());
	}
	virtual void paint(juce::Graphics&) override
	{
	}
};

FilePlaybackAudioProcessorEditor* FilePlaybackAudioProcessorEditor::createInstance(FilePlaybackAudioProcessor& p)
{
	return new FilePlaybackAudioProcessorEditorImpl(p);
}
