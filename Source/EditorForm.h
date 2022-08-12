/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveformView.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class EditorForm  : public juce::Component,
                    public juce::ApplicationCommandTarget,
                    public juce::FileDragAndDropTarget,
                    public juce::Timer,
                    public FilePlaybackAudioProcessor::Listener,
                    public juce::Label::Listener
{
public:
    //==============================================================================
    EditorForm (FilePlaybackAudioProcessor* p);
    ~EditorForm() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    bool tryCmdMgrInit();
    // public juce::ApplicationCommandTarget
    virtual juce::ApplicationCommandTarget* getNextCommandTarget() override;
    virtual void getAllCommands(juce::Array<juce::CommandID>&) override;
    virtual void getCommandInfo(juce::CommandID, juce::ApplicationCommandInfo&) override;
    virtual bool perform(const juce::ApplicationCommandTarget::InvocationInfo&) override;
    // juce::FileDragAndDropTarget
    virtual bool isInterestedInFileDrag(const juce::StringArray& files) override;
    virtual void filesDropped(const juce::StringArray& files, int x, int y) override;
    // juce::Timer
    virtual void timerCallback() override;
    // FilePlaybackAudioProcessor::Listener
    virtual void propertyDidChange(FilePlaybackAudioProcessor*, FPPID pid) override;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void labelTextChanged (juce::Label* labelThatHasChanged) override;
    void visibilityChanged() override;
    void parentHierarchyChanged() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    juce::ApplicationCommandManager mCommandManager;
    bool mCmdMgrInitDone = false;
    FilePlaybackAudioProcessor* mProcessor;
    std::unique_ptr<juce::FileChooser> mFileChooser;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> mFileLabel;
    std::unique_ptr<juce::Label> mFilePathLabel;
    std::unique_ptr<juce::TextButton> mFileCloseButton;
    std::unique_ptr<juce::TextButton> mFileBrowseButton;
    std::unique_ptr<WaveformView> mWaveformView;
    std::unique_ptr<juce::TextButton> mRunButton;
    std::unique_ptr<juce::TextButton> mFastBwdButton;
    std::unique_ptr<juce::TextButton> mFastFwdButton;
    std::unique_ptr<juce::ToggleButton> mLoopingButton;
    std::unique_ptr<juce::Label> mCursorTimeLabel;
    std::unique_ptr<juce::Label> mGainLabel;
    std::unique_ptr<juce::Slider> mGainSlider;
    std::unique_ptr<juce::Label> mSpeedLabel;
    std::unique_ptr<juce::Slider> mSpeedSlider;
    std::unique_ptr<juce::Label> mCursorTimeEdit;
    std::unique_ptr<juce::Label> mLoopBeginLabel;
    std::unique_ptr<juce::Label> mLoopBeginEdit;
    std::unique_ptr<juce::Label> mLoopEndLabel;
    std::unique_ptr<juce::Label> mLoopEndEdit;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorForm)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

