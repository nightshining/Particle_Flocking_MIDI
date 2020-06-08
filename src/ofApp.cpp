#include "ofApp.h"
//addind note
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    ofEnableAntiAliasing();
    
    speed = 0.1f;
    
    midi.setupMidiDevice("UM-ONE");
    font.load("font/Arial.ttf", 10);
    //logo.load("image/nslogo.png");
    
    const int total = 20;
    motion.resize(total);
    
    
    int keyboardCC[] = { 14,34,35,36,37,
                         24,25,26,41,43,
                         44,48,49,52,53,
                         54,81,82,30,31, };
    
    ccIndex.assign(keyboardCC, keyboardCC + total);
    reset(total);
    

    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i = 0; i < motion.size(); i++ ) {
        
        motion[i].update();
        
        int valMapped = ofMap(motion[i].getPosition().x, 0.0f, 1.0f, 0, 127);
        
        midi.setMidiCC(1, ccIndex[i], valMapped);
        
//        cout << i << " " << motion[i].getPosition().x << endl;
        
    }
}
void ofApp::exit(){
    
    
}

void ofApp::reset(int size) {
    
    ccController.clear();

    for(int i = 0; i < size; i++ ) {
        
    motion[i].reset();
    
        ///set an array of booleans that will randomly choose whether we have X or Y pos effect our parameters
        int bR = ofRandom(2);
        if (bR == 0) {
            ccController.push_back(0);
        } else {
            ccController.push_back(1);
        }
        
        //cout << "CC: " << ccIndex[i] << endl;
        //cout << "XY: " << ccController[i] << endl;
    }

}
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofVec2f p = ofVec2f(ofGetWidth()*0.05,ofGetHeight()*0.1);
    
    //ofDrawBitmapString("Speed: " + ofToString(speed), p);
    
    for(int i = 0; i < motion.size(); i++ ) {
        motion[i].display();
        ofVec2f ccIndexPos = ofVec2f(ofGetWidth()*0.05,ofGetHeight() * 0.18 + i * 18);
        
        int valMapped;
        char label;
        
        if (ccController[i] == true) {
            valMapped = ofMap(motion[i].getPosition().x, 0.0f, 1.0f, 0, 127);
            label = 'X';
        } else {
            valMapped = ofMap(motion[i].getPosition().y, 0.0f, 1.0f, 0, 127);
            label = 'Y';
        }
        //ofDrawBitmapString("CC " + ofToString(i) + " " + ofToString(valMapped), ccIndex);
        font.drawString("CC " + ofToString(ccIndex[i]) + ": " + ofToString(valMapped) + " " + label, ccIndexPos.x,ccIndexPos.y);
        
    }
    
    
    font.drawString("Speed: " + ofToString(speed), p.x,p.y);
    

  
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


    if ( key == OF_KEY_UP ) {
        speed += 0.1;
    }
    
    if ( key == OF_KEY_DOWN ) {
        speed -= 0.1;
    }
    
    if ( key == OF_KEY_LEFT ) {
        speed -= 1.0;
    }
    
    if ( key == OF_KEY_RIGHT ) {
        speed += 1.0;
    }
    
    if ( key == ' ' ) {
        
        reset(motion.size());
        
    }
    
    for(int i = 0; i < motion.size(); i++ ) {
        
        motion[i].setSpeed(speed);
        
    }
    
    

 

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
