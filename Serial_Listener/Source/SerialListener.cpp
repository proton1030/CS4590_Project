/*
  ==============================================================================

    SerialListener.cpp
    Created: 9 Feb 2019 4:06:44pm
    Author:  hanyu

  ==============================================================================
*/

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include "SerialListener.h"
#include "juce_serialport.h"

using namespace std;

SerialListener::SerialListener()
{
    SerialPortConfig serialConf(115200, 8, SerialPortConfig::SerialPortParity::SERIALPORT_PARITY_NONE, SerialPortConfig::SerialPortStopBits::STOPBITS_1, SerialPortConfig::SerialPortFlowControl::FLOWCONTROL_NONE);
    
    pSerialPort = new SerialPort();
    StringRef sPortContain = "usbmodem";
    StringArray serialPortPaths = pSerialPort->getSerialPortPaths().getAllValues();
    String sPortPath;
    for (int i = 0; i < serialPortPaths.size(); i++)
        if (serialPortPaths[i].contains(sPortContain))
            sPortPath = serialPortPaths[i];
    assert(sPortPath.toStdString().size() != 0);
    delete pSerialPort;
    pSerialPort = new SerialPort(sPortPath, serialConf);
    pSerialStream = new SerialPortInputStream(pSerialPort);
    pMidiDevice = MidiOutput::createNewDevice("S-Motion");
    assert(pMidiDevice != nullptr);
    
}

SerialListener::~SerialListener() {
    pSerialPort->close();
    delete pSerialPort;
    delete pSerialStream;
    delete pMidiDevice;
}

void SerialListener::readFromPort()
{
    if (pSerialStream->canReadLine())
    {
        string s = pSerialStream->readNextLine().toStdString();
        regex format("-?\\d+.\\d+,-?\\d+.\\d+,-?\\d+.\\d+");
        if (regex_match(s, format))
        {
            std::replace(s.begin(), s.end(), ',', ' ');
            cout << s << endl;
            std::istringstream iss(s);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            for (size_t i = 0; i < 3; i++)
            {
                data[i] = ((stof(results[i]) + 180.0) / 2.9 - 20)*1.2;
            }
            
            if (channelIsActive[0])
                pMidiDevice->sendMessageNow(MidiMessage(0xB0, 0x00, (uint8)data[2]));
            if (channelIsActive[1])
                pMidiDevice->sendMessageNow(MidiMessage(0xB0, 0x01, (uint8)data[1]));
            
            cout << (uint8)data[2] << " " << (uint8)data[1] << endl;
        }
        
    }
//
    
    
    
}


void SerialListener::timerCallback()
{
    readFromPort();
}

void SerialListener::setChannelActive(size_t channelNum, bool activeOrNot)
{
    channelIsActive[channelNum] = activeOrNot;
}
