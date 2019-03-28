/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "SerialListener.h"

using namespace std;

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (300, 200);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    serial = new SerialListener();
    setWantsKeyboardFocus(true);
    serial->startTimer(1);
    
    addAndMakeVisible(ctrl1);
    ctrl1.setButtonText("Roll Ctrl");
    ctrl1.setClickingTogglesState(true);
    ctrl1.addListener(this);
    
    addAndMakeVisible(ctrl2);
    ctrl2.setButtonText("Pitch Ctrl");
    ctrl2.setClickingTogglesState(true);
    ctrl2.addListener(this);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    delete serial;
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{

}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{

    bufferToFill.clearActiveBufferRegion();
    
}

void MainComponent::releaseResources()
{

}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!

}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    ctrl1.setBounds(20, 20, 150, 40);
    ctrl2.setBounds(20, 80, 150, 40);
}

void MainComponent::buttonClicked(Button *btn)
{
    if (btn == &ctrl1)
    {
        serial->setChannelActive(0, ctrl1.getToggleState());
    }
    else
    {
        serial->setChannelActive(1, ctrl2.getToggleState());
    }
}

void MainComponent::buttonStateChanged(Button *btn)
{


}
