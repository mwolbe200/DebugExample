/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class DebugExampleAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    //==============================================================================
    DebugExampleAudioProcessorEditor (DebugExampleAudioProcessor& p);
    ~DebugExampleAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    DebugExampleAudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebugExampleAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
