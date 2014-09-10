#pragma once

#include "ofMain.h"
#include "particle.h"


enum PlayState {STATE_BLANK, STATE_NEW_MESSAGE,STATE_WAIT,STATE_REMOVE_ALL};

class ofApp : public ofBaseApp{

    std::vector<Particle*> particles;
    ofImage txtData;
    
	public:
		void setup();
		void update();
		void draw();
    
    void removeAll();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    PlayState currentState;
    void startParticles();
    std::vector<ofVec2f> vboPoints;
    std::vector<ofFloatColor> vboColors;

    
    ofVec2f getField(ofVec2f* position);
   
    float fallOffTriger;
    float newMessage;
    float removeAllTriger;
    
    ofVbo vbo;

};
