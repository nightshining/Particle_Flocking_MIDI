#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class MIDI {
    
public:
    ofxMidiIn midiIn;

    MIDI() {
        midiOut.listOutPorts();
        //midiIn.addListener(this);
        midiIn.ignoreTypes(false, false, false);
        // print received messages to the console
        midiIn.setVerbose(true);
    }
    void setupMidiDevice(string device) {
        // "IAC Driver Pure Data In"
        midiOut.openPort(device);
       
    }
    
    int getMIDICCTotal() {
        
        // get midi cc amount here //
        return 0;
    }
    
    void setMidiCC(int channel, int ccNum, int ccVal) {
        
        midiOut.sendControlChange( channel, ccNum, ccVal );
        

    }
    
    void exit() {
        midiIn.closePort();
       // midiIn.removeListener(this);
    }
    
    
    void readMIDIController() {
          
        for(unsigned int i = 0; i < midiMessages.size(); ++i) {
            
            ofxMidiMessage &message = midiMessages[i];
            int x = 10;
            int y = i * 40 + 40;
            
            // draw the last recieved message contents to the screen,
            // this doesn't print all the data from every status type
            // but you should get the general idea
            stringstream text;
            text << ofxMidiMessage::getStatusString(message.status);
            while(text.str().length() < 16) { // pad status width
                text << " ";
            }
            
            ofSetColor(127);
            if(message.status < MIDI_SYSEX) {
                text << "chan: " << message.channel;
                if(message.status == MIDI_CONTROL_CHANGE) {
                    text << "\tctl: " << message.control;
                    ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
                                    ofMap(message.control, 0, 127, 0, ofGetWidth()*0.2), 10);
                }
                else if(message.status == MIDI_PITCH_BEND) {
                    text << "\tval: " << message.value;
                    ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
                                    ofMap(message.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()*0.2), 10);
                }
                else {
                    text << "\tpitch: " << message.pitch;
                    ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
                                    ofMap(message.pitch, 0, 127, 0, ofGetWidth()*0.2), 10);
                    
                    text << "\tvel: " << message.velocity;
                    ofDrawRectangle(x + (ofGetWidth()*0.2 * 2), y + 12,
                                    ofMap(message.velocity, 0, 127, 0, ofGetWidth()*0.2), 10);
                }
                text << " "; // pad for delta print
            }
            
            text << "delta: " << message.deltatime;
            ofSetColor(0);
            ofDrawBitmapString(text.str(), x, y);
            text.str(""); // clear
        }
        
    };
    
    void newMidiMessage(ofxMidiMessage& msg) {
        
        // add the latest message to the message queue
        midiMessages.push_back(msg);
        // remove any old messages if we have too many
        while(midiMessages.size() > maxMessages) {
            midiMessages.erase(midiMessages.begin());
        }
    }

    
    
    
private:
    
    bool bPrintOut = false;
    ofxMidiOut midiOut;

    
    std::vector<ofxMidiMessage> midiMessages;
    std::size_t maxMessages = 10; //< max number of messages to keep track of

    
};


