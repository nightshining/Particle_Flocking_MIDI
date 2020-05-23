
#include "ofMain.h"

class Mover {

public:
   
    
    Mover() {
        // Start in the center
        position = ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
        velocity = ofVec2f(0,0);
        topspeed = 5;
        accel = 0.2f;
    }
    
    void reset() {
        
        position = ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));

    }
    void update() {
        
        // Compute a vector that points from position to mouse
        mouse = ofVec2f(ofGetMouseX(), ofGetMouseY());
        acceleration = mouse - position; //ofVec2f.sub(mouse,position);
        
        // Set magnitude of acceleration
        //acceleration.setMag(0.2);
        acceleration.normalize();
        acceleration.operator*=(accel);
        
        // Velocity changes according to acceleration
        velocity.operator+=(acceleration);
        // Limit the velocity by topspeed
        velocity.limit(topspeed);
        // position changes by velocity
        position.operator+=(velocity);
    }
    
    void display() {
        
        ofSetColor(0);
        ofFill();
        ofDrawEllipse(position.x,position.y,15,15);

    }
    
    void setSpeed(float s) { topspeed = s; };
    
        ofVec2f getPosition() {
        ofVec2f p = ofVec2f(abs(position.x), abs(position.y));
        return p.normalize();
    };
    
    ofVec2f getNormal() {
        
//        float x = ofNormalize(velocity.x, abs(mouse.x), abs(position.x));
//        float y = ofNormalize(velocity.y, abs(mouse.y), abs(position.y));
//        ofVec2f p = ofVec2f( x, y );

        float d = ofDist(mouse.x,mouse.y,position.x,position.y);

        float x = ofNormalize(position.x, 0, abs(d));
        float y = ofNormalize(position.y, 0, abs(d));
        ofVec2f p = position;
        
        return p.normalize();

    }
    
    float dist() {
        
        float d = ofDist(mouse.x,mouse.y,position.x,position.y);
        return d;
    }
    
    
    
private:
    
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f mouse;
    
    float topspeed;
    float accel;
    //this should be same number as amount of movers
    const int n = 300;
};
