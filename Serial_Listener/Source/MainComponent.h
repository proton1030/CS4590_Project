/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SerialListener.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent, public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

    // bool keyPressed(const KeyPress &key, Component* originatingComponent) override;
    // bool keyStateChanged(bool isKeyDown, Component* originatingComponent) override;

    

private:
    //==============================================================================
    // Your private member variables go here...
    SerialListener *serial;
    
    TextButton ctrl1, ctrl2;
    
    void buttonClicked(Button *btn) override;
    void buttonStateChanged(Button *btn) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
