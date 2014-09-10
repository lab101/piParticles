//
//  particle.h
//  particles
//
//  Created by lab101 on 08/09/14.
//
//

#ifndef __particles__particle__
#define __particles__particle__

#include <iostream>
#include "ofMain.h"

class Particle {
public:
    ofVec2f* position;
    ofVec2f targetPosition;

    ofVec2f offset;
    ofVec2f pushForce;
    ofVec2f fallOffForce;

    ofFloatColor* color;
    float delay;
    float waitTime;
    float fallOffDelay;

    bool isMoving;
    bool isFallOff;
    
    string data;
    
    void startFallOff(float delay);
    void update();
    void draw();
    
    Particle();
};

#endif /* defined(__particles__particle__) */
