/*
  ==============================================================================

    SerialListener.h
    Created: 9 Feb 2019 4:06:44pm
    Author:  hanyu

  ==============================================================================
*/

#pragma once

#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>

#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_serialport.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class SerialListener : public Timer
{
public:
    //==============================================================================
    SerialListener();
    ~SerialListener();

    void readFromPort();
    void timerCallback() override;
    void setChannelActive(size_t channelNum, bool activeOrNot);

private:
    //==============================================================================
    // Your private member variables go here...
    
    SerialPort *pSerialPort;
    SerialPortInputStream *pSerialStream;
    MidiOutput *pMidiDevice;
    
    float   data[3];
    bool    channelIsActive[2] = {false, false};
    
//    void handleIncomingMidiMessage (MidiInput *source, const MidiMessage &message) override;
//    void handlePartialSysexMessage (MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SerialListener)
};
