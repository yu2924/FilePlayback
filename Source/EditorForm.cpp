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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "EditorForm.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
enum CommandIDs
{
    ToggleRun = 1,
    Rewind,
    FastBwd,
    FastFwd,
    ToggleLoop,
    ClearFile,
    BrowseFile,
};
//[/MiscUserDefs]

//==============================================================================
EditorForm::EditorForm (FilePlaybackAudioProcessor* p)
    : mProcessor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    mFileLabel.reset (new juce::Label ("new label",
                                       TRANS("file")));
    addAndMakeVisible (mFileLabel.get());
    mFileLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mFileLabel->setJustificationType (juce::Justification::centredLeft);
    mFileLabel->setEditable (false, false, false);
    mFileLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mFileLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    mFileLabel->setBounds (8, 8, 40, 20);

    mFilePathLabel.reset (new juce::Label (juce::String(),
                                           juce::String()));
    addAndMakeVisible (mFilePathLabel.get());
    mFilePathLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mFilePathLabel->setJustificationType (juce::Justification::centredLeft);
    mFilePathLabel->setEditable (false, false, false);
    mFilePathLabel->setColour (juce::Label::outlineColourId, juce::Colour (0xffdddddd));
    mFilePathLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mFilePathLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    mFileCloseButton.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (mFileCloseButton.get());
    mFileCloseButton->setButtonText (TRANS("x"));

    mFileBrowseButton.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (mFileBrowseButton.get());
    mFileBrowseButton->setButtonText (TRANS("..."));

    mWaveformView.reset (new WaveformView (mProcessor->getSharedResource()->audioFormatManager, mProcessor->getSharedResource()->audioThumbnailCache));
    addAndMakeVisible (mWaveformView.get());

    mRunButton.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (mRunButton.get());
    mRunButton->setButtonText (TRANS("run"));

    mRunButton->setBounds (8, 232, 80, 56);

    mFastBwdButton.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (mFastBwdButton.get());
    mFastBwdButton->setButtonText (TRANS("<<"));

    mFastBwdButton->setBounds (96, 264, 40, 24);

    mFastFwdButton.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (mFastFwdButton.get());
    mFastFwdButton->setButtonText (TRANS(">>"));

    mFastFwdButton->setBounds (136, 264, 40, 24);

    mLoopingButton.reset (new juce::ToggleButton (juce::String()));
    addAndMakeVisible (mLoopingButton.get());
    mLoopingButton->setButtonText (TRANS("loop"));

    mLoopingButton->setBounds (96, 232, 80, 24);

    mCursorTimeLabel.reset (new juce::Label (juce::String(),
                                             TRANS("cursor")));
    addAndMakeVisible (mCursorTimeLabel.get());
    mCursorTimeLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mCursorTimeLabel->setJustificationType (juce::Justification::centredRight);
    mCursorTimeLabel->setEditable (false, false, false);
    mCursorTimeLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mCursorTimeLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    mCursorTimeLabel->setBounds (432, 232, 56, 24);

    mGainLabel.reset (new juce::Label (juce::String(),
                                       TRANS("gain")));
    addAndMakeVisible (mGainLabel.get());
    mGainLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mGainLabel->setJustificationType (juce::Justification::centredRight);
    mGainLabel->setEditable (false, false, false);
    mGainLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mGainLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    mGainLabel->setBounds (184, 264, 48, 24);

    mGainSlider.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (mGainSlider.get());
    mGainSlider->setRange (-60, 20, 0.1);
    mGainSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    mGainSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 60, 20);

    mGainSlider->setBounds (232, 264, 200, 24);

    mSpeedLabel.reset (new juce::Label (juce::String(),
                                        TRANS("speed")));
    addAndMakeVisible (mSpeedLabel.get());
    mSpeedLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mSpeedLabel->setJustificationType (juce::Justification::centredRight);
    mSpeedLabel->setEditable (false, false, false);
    mSpeedLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mSpeedLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    mSpeedLabel->setBounds (184, 232, 48, 24);

    mSpeedSlider.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (mSpeedSlider.get());
    mSpeedSlider->setRange (-1, 1, 0.001);
    mSpeedSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    mSpeedSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 60, 20);

    mSpeedSlider->setBounds (232, 232, 200, 24);

    mCursorTimeEdit.reset (new juce::Label (juce::String(),
                                            TRANS("0")));
    addAndMakeVisible (mCursorTimeEdit.get());
    mCursorTimeEdit->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mCursorTimeEdit->setJustificationType (juce::Justification::centredRight);
    mCursorTimeEdit->setEditable (true, true, false);
    mCursorTimeEdit->setColour (juce::Label::outlineColourId, juce::Colour (0xffdddddd));
    mCursorTimeEdit->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mCursorTimeEdit->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    mCursorTimeEdit->addListener (this);

    mCursorTimeEdit->setBounds (488, 232, 64, 24);

    mLoopBeginLabel.reset (new juce::Label (juce::String(),
                                            TRANS("loop begin")));
    addAndMakeVisible (mLoopBeginLabel.get());
    mLoopBeginLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mLoopBeginLabel->setJustificationType (juce::Justification::centredRight);
    mLoopBeginLabel->setEditable (false, false, false);
    mLoopBeginLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mLoopBeginLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    mLoopBeginLabel->setBounds (560, 232, 80, 24);

    mLoopBeginEdit.reset (new juce::Label (juce::String(),
                                           TRANS("0")));
    addAndMakeVisible (mLoopBeginEdit.get());
    mLoopBeginEdit->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mLoopBeginEdit->setJustificationType (juce::Justification::centredRight);
    mLoopBeginEdit->setEditable (true, true, false);
    mLoopBeginEdit->setColour (juce::Label::outlineColourId, juce::Colour (0xffdddddd));
    mLoopBeginEdit->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mLoopBeginEdit->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    mLoopBeginEdit->addListener (this);

    mLoopBeginEdit->setBounds (640, 232, 64, 24);

    mLoopEndLabel.reset (new juce::Label (juce::String(),
                                          TRANS("loop end")));
    addAndMakeVisible (mLoopEndLabel.get());
    mLoopEndLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mLoopEndLabel->setJustificationType (juce::Justification::centredRight);
    mLoopEndLabel->setEditable (false, false, false);
    mLoopEndLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mLoopEndLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    mLoopEndLabel->setBounds (560, 264, 80, 24);

    mLoopEndEdit.reset (new juce::Label (juce::String(),
                                         TRANS("0")));
    addAndMakeVisible (mLoopEndEdit.get());
    mLoopEndEdit->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mLoopEndEdit->setJustificationType (juce::Justification::centredRight);
    mLoopEndEdit->setEditable (true, true, false);
    mLoopEndEdit->setColour (juce::Label::textColourId, juce::Colours::black);
    mLoopEndEdit->setColour (juce::Label::outlineColourId, juce::Colour (0xffdddddd));
    mLoopEndEdit->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mLoopEndEdit->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    mLoopEndEdit->setColour (juce::TextEditor::highlightColourId, juce::Colour (0xbfffa500));
    mLoopEndEdit->addListener (this);

    mLoopEndEdit->setBounds (640, 264, 64, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 296);


    //[Constructor] You can add your own custom stuff here..
    mCommandManager.registerAllCommandsForTarget(this);
    mFileCloseButton->setCommandToTrigger(&mCommandManager, CommandIDs::ClearFile, true);
    mFileBrowseButton->setCommandToTrigger(&mCommandManager, CommandIDs::BrowseFile, true);
    mRunButton->setCommandToTrigger(&mCommandManager, CommandIDs::ToggleRun, true);
    mFastBwdButton->setRepeatSpeed(200, 100);
    mFastBwdButton->setCommandToTrigger(&mCommandManager, CommandIDs::FastBwd, true);
    mFastFwdButton->setRepeatSpeed(200, 100);
    mFastFwdButton->setCommandToTrigger(&mCommandManager, CommandIDs::FastFwd, true);
    mLoopingButton->setClickingTogglesState(false);
    mLoopingButton->setCommandToTrigger(&mCommandManager, CommandIDs::ToggleLoop, true);
    mWaveformView->onChangeCursorTime = [this](double t)
    {
        mProcessor->setPlaybackTime(t);
    };
    mWaveformView->onChangeLoopRange = [this](TimeRange tr)
    {
        mProcessor->setLoopRange(tr);
    };
    mSpeedSlider->setDoubleClickReturnValue(true, 0);
    mSpeedSlider->textFromValueFunction = [this](double v)->juce::String
    {
        double p = juce::jlimit(-1.0, 1.0, v);
        double r = pow(2, p);
        return juce::String::formatted("%.3f", r);
    };
    mSpeedSlider->valueFromTextFunction = [this](const juce::String& s)->double
    {
        double r = juce::jlimit(0.5, 2.0, s.getDoubleValue());
        double p = log2(r);
        return p;
    };
    mSpeedSlider->onValueChange = [this]()
    {
        double p = juce::jlimit(-1.0, 1.0, mSpeedSlider->getValue());
        double r = pow(2, p);
        mProcessor->setSpeed(r);
    };
    mGainSlider->setDoubleClickReturnValue(true, 0);
    mGainSlider->textFromValueFunction = [this](double v)->juce::String
    {
        if(v <= -60) return "off";
        else return juce::String::formatted("%.1f", v);
    };
    mGainSlider->valueFromTextFunction = [this](const juce::String& s)->double
    {
        if(s.trimStart().startsWithIgnoreCase("off")) return -60;
        else return s.getDoubleValue();
    };
    mGainSlider->onValueChange = [this]()
    {
        double db = mGainSlider->getValue();
        double a = (-60 < db) ? pow(10, db * 0.05) : 0;
        mProcessor->setGain((float)a);
    };
    mCursorTimeEdit->onTextChange = [this]()
    {
        mProcessor->setPlaybackTime(mCursorTimeEdit->getText().getDoubleValue());
    };
    mLoopBeginEdit->onTextChange = [this]()
    {
        TimeRange tr = mProcessor->getLoopRange();
        tr.begin = mLoopBeginEdit->getText().getDoubleValue();
        mProcessor->setLoopRange(tr);
    };
    mLoopEndEdit->onTextChange = [this]()
    {
        TimeRange tr = mProcessor->getLoopRange();
        tr.end = mLoopEndEdit->getText().getDoubleValue();
        mProcessor->setLoopRange(tr);
    };
    propertyDidChange(mProcessor, FPPID::File);
    propertyDidChange(mProcessor, FPPID::Speed);
    propertyDidChange(mProcessor, FPPID::Gain);
    propertyDidChange(mProcessor, FPPID::LoopRange);
    propertyDidChange(mProcessor, FPPID::Looping);
    propertyDidChange(mProcessor, FPPID::Running);
    propertyDidChange(mProcessor, FPPID::PlaybackTime);
    mProcessor->addListener(this);
    //[/Constructor]
}

EditorForm::~EditorForm()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    mProcessor->removeListener(this);
    //[/Destructor_pre]

    mFileLabel = nullptr;
    mFilePathLabel = nullptr;
    mFileCloseButton = nullptr;
    mFileBrowseButton = nullptr;
    mWaveformView = nullptr;
    mRunButton = nullptr;
    mFastBwdButton = nullptr;
    mFastFwdButton = nullptr;
    mLoopingButton = nullptr;
    mCursorTimeLabel = nullptr;
    mGainLabel = nullptr;
    mGainSlider = nullptr;
    mSpeedLabel = nullptr;
    mSpeedSlider = nullptr;
    mCursorTimeEdit = nullptr;
    mLoopBeginLabel = nullptr;
    mLoopBeginEdit = nullptr;
    mLoopEndLabel = nullptr;
    mLoopEndEdit = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EditorForm::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void EditorForm::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    mFilePathLabel->setBounds (48, 8, getWidth() - 104, 20);
    mFileCloseButton->setBounds (getWidth() - 56, 8, 24, 20);
    mFileBrowseButton->setBounds (getWidth() - 32, 8, 24, 20);
    mWaveformView->setBounds (8, 32, getWidth() - 16, 192);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EditorForm::labelTextChanged (juce::Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == mCursorTimeEdit.get())
    {
        //[UserLabelCode_mCursorTimeEdit] -- add your label text handling code here..
        //[/UserLabelCode_mCursorTimeEdit]
    }
    else if (labelThatHasChanged == mLoopBeginEdit.get())
    {
        //[UserLabelCode_mLoopBeginEdit] -- add your label text handling code here..
        //[/UserLabelCode_mLoopBeginEdit]
    }
    else if (labelThatHasChanged == mLoopEndEdit.get())
    {
        //[UserLabelCode_mLoopEndEdit] -- add your label text handling code here..
        //[/UserLabelCode_mLoopEndEdit]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

void EditorForm::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
    tryCmdMgrInit();
    //[/UserCode_visibilityChanged]
}

void EditorForm::parentHierarchyChanged()
{
    //[UserCode_parentHierarchyChanged] -- Add your code here...
    tryCmdMgrInit();
    //[/UserCode_parentHierarchyChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

bool EditorForm::tryCmdMgrInit()
{
    if(mCmdMgrInitDone) return false;
    Component* top = getTopLevelComponent();
    if(!top || !top->isOnDesktop() || !isShowing()) return false;
    top->addKeyListener(mCommandManager.getKeyMappings());
    mCommandManager.setFirstCommandTarget(this);
    grabKeyboardFocus();
    mCmdMgrInitDone = true;
    return true;
}

// public juce::ApplicationCommandTarget
juce::ApplicationCommandTarget* EditorForm::getNextCommandTarget()
{
    return nullptr;
}

void EditorForm::getAllCommands(juce::Array<juce::CommandID>& cmdids)
{
    juce::Array<juce::CommandID> ids
    {
        CommandIDs::ToggleRun,
        CommandIDs::Rewind,
        CommandIDs::FastBwd,
        CommandIDs::FastFwd,
        CommandIDs::ToggleLoop,
        CommandIDs::ClearFile,
        CommandIDs::BrowseFile,
    };
    cmdids.addArray(ids);
}

void EditorForm::getCommandInfo(juce::CommandID cmdid, juce::ApplicationCommandInfo& info)
{
    switch(cmdid)
    {
        case CommandIDs::ToggleRun:
            info.setInfo("run", "toggle start/stop", "command", 0);
            info.addDefaultKeypress(juce::KeyPress::spaceKey, 0);
            info.setTicked(mProcessor->isRunning());
            info.setActive(true);
            break;
        case CommandIDs::Rewind:
            info.setInfo("rewind", "rewind", "command", 0);
            info.addDefaultKeypress('w', 0);
            info.setActive(true);
            break;
        case CommandIDs::FastBwd:
            info.setInfo("fastbwd", "fast backward", "command", 0);
            info.addDefaultKeypress(juce::KeyPress::leftKey, juce::ModifierKeys::altModifier);
            info.setActive(true);
            break;
        case CommandIDs::FastFwd:
            info.setInfo("fasfbwd", "fast forward", "command", 0);
            info.addDefaultKeypress(juce::KeyPress::rightKey, juce::ModifierKeys::altModifier);
            info.setActive(true);
            break;
        case CommandIDs::ToggleLoop:
            info.setInfo("loop", "toggle loop", "command", 0);
            info.addDefaultKeypress('l', juce::ModifierKeys::altModifier);
            info.setTicked(mProcessor->isLooping());
            info.setActive(true);
            break;
        case CommandIDs::ClearFile:
            info.setInfo("clear", "clear", "command", 0);
            info.setActive(true);
            break;
        case CommandIDs::BrowseFile:
            info.setInfo("browse", "browse", "command", 0);
            info.setActive(true);
            break;
        default: break;
    }
}

bool EditorForm::perform(const juce::ApplicationCommandTarget::InvocationInfo& info)
{
    switch(info.commandID)
    {
        case CommandIDs::ToggleRun:
            mProcessor->setRunning(!mProcessor->isRunning());
            return true;
        case CommandIDs::Rewind:
            mProcessor->setPlaybackTime(0);
            return true;
        case CommandIDs::FastBwd:
            mProcessor->setPlaybackTime(mProcessor->getPlaybackTime() - 1);
            return true;
        case CommandIDs::FastFwd:
            mProcessor->setPlaybackTime(mProcessor->getPlaybackTime() + 1);
            return true;
        case CommandIDs::ToggleLoop:
            mProcessor->setLooping(!mProcessor->isLooping());
            return true;
        case CommandIDs::ClearFile:
            mProcessor->setFile(juce::File());
            return true;
        case CommandIDs::BrowseFile:
        {
            mFileChooser.reset(new juce::FileChooser("", mProcessor->getFile(), mProcessor->getSharedResource()->audioFormatManager.getWildcardForAllFormats(), true, false, this));
            int flg = juce::FileBrowserComponent::FileChooserFlags::openMode | juce::FileBrowserComponent::FileChooserFlags::canSelectFiles;
            mFileChooser->launchAsync(flg, [this](const juce::FileChooser& dlg)
            {
                juce::File path = dlg.getResult();
                if(path != juce::File()) mProcessor->setFile(path);
                mFileChooser.reset();
            });
            return true;
        }
        default:
            return false;
    }
}

// juce::FileDragAndDropTarget
bool EditorForm::isInterestedInFileDrag(const juce::StringArray& files)
{
    if(files.isEmpty() || (1 < files.size())) return false;
    return mProcessor->getSharedResource()->audioFormatManager.findFormatForFileExtension(juce::File(files[0]).getFileExtension()) != nullptr;
}

void EditorForm::filesDropped(const juce::StringArray& files, int, int)
{
    if(!isInterestedInFileDrag(files)) return;
    mProcessor->setFile(juce::File(files[0]));
}

//juce::Timer
void EditorForm::timerCallback()
{
    double t = mProcessor->getPlaybackTime();
    mWaveformView->setPlaybackTime(t);
    mCursorTimeEdit->setText(juce::String(t), juce::NotificationType::dontSendNotification);
}

// FilePlaybackAudioProcessor::Listener
void EditorForm::propertyDidChange(FilePlaybackAudioProcessor*, FPPID pid)
{
    switch(pid)
    {
        case FPPID::File:
            mFilePathLabel->setText(mProcessor->getFile().getFullPathName(), juce::NotificationType::dontSendNotification);
            mWaveformView->setFile(mProcessor->getFile());
            propertyDidChange(mProcessor, FPPID::LoopRange);
            break;
        case FPPID::Speed:
        {
            double r = juce::jlimit(0.5, 2.0, mProcessor->getSpeed());
            double p = log2(r);
            mSpeedSlider->setValue(p, juce::NotificationType::dontSendNotification);
            break;
        }
        case FPPID::Gain:
        {
            float a = mProcessor->getGain();
            float db = (0.001f < a) ? (20 * log10(a)) : -60;
            mGainSlider->setValue(db, juce::NotificationType::dontSendNotification);
            break;
        }
        case FPPID::LoopRange:
        {
            TimeRange tr = mProcessor->getLoopRange();
            mWaveformView->setLoopRange(tr);
            mLoopBeginEdit->setText(juce::String(tr.begin), juce::NotificationType::dontSendNotification);
            mLoopEndEdit->setText(juce::String(tr.end), juce::NotificationType::dontSendNotification);
            break;
        }
        case FPPID::Looping:
            mLoopingButton->setToggleState(mProcessor->isLooping(), juce::NotificationType::dontSendNotification);
            break;
        case FPPID::Running:
        {
            bool prunning = mProcessor->isRunning();
            bool trunning = isTimerRunning();
            mRunButton->setToggleState(prunning, juce::NotificationType::dontSendNotification);
            if(prunning && !trunning) startTimer(100);
            else if(!prunning && trunning) stopTimer();
            if(!prunning) mWaveformView->setPlaybackTime(mProcessor->getPlaybackTime());
            break;
        }
        case FPPID::PlaybackTime:
        {
            double t = mProcessor->getPlaybackTime();
            mWaveformView->setPlaybackTime(t);
            mCursorTimeEdit->setText(juce::String(t), juce::NotificationType::dontSendNotification);
            break;
        }
        default:
            break;
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="EditorForm" componentName=""
                 parentClasses="public juce::Component, public juce::ApplicationCommandTarget, public juce::FileDragAndDropTarget, public juce::Timer, public FilePlaybackAudioProcessor::Listener"
                 constructorParams="FilePlaybackAudioProcessor* p" variableInitialisers="mProcessor(p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="800" initialHeight="296">
  <METHODS>
    <METHOD name="parentHierarchyChanged()"/>
    <METHOD name="visibilityChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="new label" id="fa025f9941bfdcf2" memberName="mFileLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 40 20" edTextCol="ff000000"
         edBkgCol="0" labelText="file" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="2b15ebd5b406318d" memberName="mFilePathLabel" virtualName=""
         explicitFocusOrder="0" pos="48 8 104M 20" outlineCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="15519550e2748662" memberName="mFileCloseButton" virtualName=""
              explicitFocusOrder="0" pos="56R 8 24 20" buttonText="x" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d1ab08c0d21dfa17" memberName="mFileBrowseButton"
              virtualName="" explicitFocusOrder="0" pos="32R 8 24 20" buttonText="..."
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="763ebecf65089765" memberName="mWaveformView" virtualName=""
                    explicitFocusOrder="0" pos="8 32 16M 192" class="WaveformView"
                    params="mProcessor-&gt;getSharedResource()-&gt;audioFormatManager, mProcessor-&gt;getSharedResource()-&gt;audioThumbnailCache"/>
  <TEXTBUTTON name="" id="d0094bc0802713fb" memberName="mRunButton" virtualName=""
              explicitFocusOrder="0" pos="8 232 80 56" buttonText="run" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="2348a438696b5353" memberName="mFastBwdButton" virtualName=""
              explicitFocusOrder="0" pos="96 264 40 24" buttonText="&lt;&lt;"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="" id="31e6cfd283631103" memberName="mFastFwdButton" virtualName=""
              explicitFocusOrder="0" pos="136 264 40 24" buttonText="&gt;&gt;"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TOGGLEBUTTON name="" id="394e5ac24e6ee1a4" memberName="mLoopingButton" virtualName=""
                explicitFocusOrder="0" pos="96 232 80 24" buttonText="loop" connectedEdges="0"
                needsCallback="0" radioGroupId="0" state="0"/>
  <LABEL name="" id="3c1e0104f8ca1301" memberName="mCursorTimeLabel" virtualName=""
         explicitFocusOrder="0" pos="432 232 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="cursor" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="e2c8e972af3959d9" memberName="mGainLabel" virtualName=""
         explicitFocusOrder="0" pos="184 264 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <SLIDER name="" id="1c74ec3dae3f9cef" memberName="mGainSlider" virtualName=""
          explicitFocusOrder="0" pos="232 264 200 24" min="-60.0" max="20.0"
          int="0.1" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="60" textBoxHeight="20" skewFactor="1.0" needsCallback="0"/>
  <LABEL name="" id="23c3545c75e4997f" memberName="mSpeedLabel" virtualName=""
         explicitFocusOrder="0" pos="184 232 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <SLIDER name="" id="25e859664e2a6e03" memberName="mSpeedSlider" virtualName=""
          explicitFocusOrder="0" pos="232 232 200 24" min="-1.0" max="1.0"
          int="0.001" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <LABEL name="" id="1e14315c73fc6982" memberName="mCursorTimeEdit" virtualName=""
         explicitFocusOrder="0" pos="488 232 64 24" outlineCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="95800018d3543067" memberName="mLoopBeginLabel" virtualName=""
         explicitFocusOrder="0" pos="560 232 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="loop begin" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="2382f56764322532" memberName="mLoopBeginEdit" virtualName=""
         explicitFocusOrder="0" pos="640 232 64 24" outlineCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="b9a516fbd44def2c" memberName="mLoopEndLabel" virtualName=""
         explicitFocusOrder="0" pos="560 264 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="loop end" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="2b73bb175ebe68b2" memberName="mLoopEndEdit" virtualName=""
         explicitFocusOrder="0" pos="640 264 64 24" textCol="ff000000"
         outlineCol="ffdddddd" edTextCol="ff000000" edBkgCol="0" hiliteCol="bfffa500"
         labelText="0" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

