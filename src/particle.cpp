//
//  particle.cpp
//  particles
//
//  Created by lab101 on 08/09/14.
//
//

#include "particle.h"

float const drawSize = 4;

Particle::Particle(){
    isMoving = false;
    isFallOff = false;
    fallOffForce.set(0,0);
    fallOffDelay =0;
    data = "test";
}

void Particle::update(){
    
    if(!isMoving) return;
    
    if(waitTime > 0){
        waitTime-= ofGetLastFrameTime();
        return;
    }
    
    if(fallOffDelay>0){
        fallOffDelay-= ofGetLastFrameTime();
        if(fallOffDelay <=0 ){
            isFallOff = true;
            fallOffForce.set(-0.01,-0.01);
        }
    }
    
    ofVec2f speed = ofVec2f(0.01, 0.01) +  (offset * 0.05);

    
    if(isFallOff && fallOffForce.length() < 150) fallOffForce *= 1.5;

    ofVec2f div = targetPosition - *position;
    
    if(!isFallOff){
        *position +=  (div * speed);
    }else{
        *position += (fallOffForce * (speed * 0.5));

    }
    
    *position += (1. - (offset * 1.0));

    
    *position += pushForce;

    pushForce.x = ofLerp(pushForce.x, 0.0,.1);
    pushForce.y = ofLerp(pushForce.y, 0.0,.1 );
}


void Particle::draw(){
  //  ofSetColor(color);
  //  ofCircle(position + (offset*230.0), offset.x * 4.);
   // ofSetCircleResolution(4);
    //ofCircle(position,6);
   // ofTriangle(*position + ofVec2f(-drawSize,drawSize), *position + ofVec2f(drawSize,drawSize), *position + ofVec2f(0,-drawSize));
}


void Particle::startFallOff(float delay){
    fallOffDelay = delay;
}