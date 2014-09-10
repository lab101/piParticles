#include "ofApp.h"


float t;

const float complexity = .8; // wind complexity
const float timeSpeed = .004; // wind variation speed
const float phase = TWO_PI; // separate u-noise from v-noise


const int gridSize  = 5;
const int dotSize  = 4;

ofVec2f ofApp::getField(ofVec2f* position) {
    
    t = ofGetFrameNum() * timeSpeed;

	float normx = ofNormalize(position->x, 0, ofGetWidth());
	float normy = ofNormalize(position->y, 0, ofGetHeight());
	float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
	float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
	return ofVec2f(u, v);
}


void ofApp::startParticles(){
  //  for (auto& p : particles)
   // {
   for(std::vector<Particle*>::iterator it = particles.begin();it != particles.end();++it )
       
   {
       Particle* p = (*it);
       
       p->offset = getField(p->position);
       p->position->set(p->targetPosition + ofVec2f(ofGetWidth(),ofGetHeight()) );
       p->waitTime = p->delay;
       p->isMoving = true;
       p->isFallOff = false;

    }
  
}

//--------------------------------------------------------------
void ofApp::setup(){

    // Rasp Pi window size
//    ofSetWindowShape(720, 480);
    
    ofSetFullscreen(true);
    ofSetFrameRate(60);
    ofHideCursor();
    ofDisableAlphaBlending();
   // ofDisableAntiAliasing();

    
    txtData.loadImage("text.png");
    unsigned char * pixels = txtData.getPixels();

    Particle* particle;
    
    int i=0;
    for (float x = 0 ; x < txtData.getWidth(); x += gridSize) {
        for (float y = 0 ; y < txtData.getHeight(); y+= gridSize ) {
            if(txtData.getColor(x, y).getBrightness() < 255){
                ++i;
            }
        }
    }
    
    // reserve space before adding otherwise the pointers get invalid by the automatic resizing of std::vector
    particles.reserve(i);
    vboColors.reserve(i);
    vboPoints.reserve(i);

    for (float x = 0 ; x < txtData.getWidth(); x += gridSize) {
        for (float y = 0 ; y < txtData.getHeight(); y+= gridSize ) {

            ofColor cur = txtData.getColor(x, y);
            
            if(cur.getBrightness() < 255){

                particle = new Particle();
                particles.push_back(particle);
                
                ofFloatColor color;
                color.set(0, 0, 22);
                ofVec2f vertex;
                vertex.set(100,100);
                
                vboColors.push_back(color);
                vboPoints.push_back(vertex);
                
                particle->color = &(vboColors.back());
                particle->position = &(vboPoints.back());
                
                particle->targetPosition.set(x,y) ;
              //  particle->targetPosition+=ofVec2f(-50,0);
                
                particle->color->set(x / txtData.getWidth() * 1.0, 0, y / txtData.getHeight() * 1.0);
                particle->delay = ofRandom(0.0,3.5);
                particle->position->set(particle->targetPosition+ ofVec2f(ofGetWidth(),ofGetHeight()));
                
            }
        }
    }
    

    startParticles();
    
    currentState = STATE_BLANK;
}

//--------------------------------------------------------------
void ofApp::update(){
   /// return;
    
    for(std::vector<Particle*>::iterator it = particles.begin();it != particles.end();++it )
    {
        
        // mouse stuff
//        ofVec2f dist = (it->position) - ofVec2f(ofGetMouseX(),ofGetMouseY());
//
//        if(dist.length() < 150){
//            
//            float force = (150-dist.length()) / 150;
//            it->pushForce += (dist * force *0.01) ;
//            
//        }

        Particle* p = (*it);
        p->offset = getField(p->position);
        p->update();
    }
    
    
    if(currentState == STATE_BLANK){
        newMessage -= ofGetLastFrameTime();
        if(newMessage <= 0){
            currentState = STATE_NEW_MESSAGE;
            removeAllTriger = 10;
            startParticles();
            fallOffTriger = ofGetElapsedTimef();
            std::cout << "new state STATE_NEW_MESSAGE " << std::endl;
        }
    }else if(currentState == STATE_NEW_MESSAGE){
        removeAllTriger -= ofGetLastFrameTime();
        
        if(fallOffTriger > 0 && (ofGetElapsedTimef() - fallOffTriger) > 0.2){
            fallOffTriger = ofGetElapsedTimef();
            int randomIndex = ofRandom(particles.size()-11);
            
            for(int i = randomIndex ; i < randomIndex + 10;++i){
                particles[i]->startFallOff(ofRandom(.8));
            }
        }
        
        if(removeAllTriger <= 0){
            currentState = STATE_REMOVE_ALL;
            std::cout << "new state STATE_REMOVE_ALL " << std::endl;

            newMessage = 13;
            removeAll();
        }
    }else if(currentState == STATE_REMOVE_ALL){
        currentState = STATE_BLANK;

    
    }

}


void ofApp::removeAll(){
    for(std::vector<Particle*>::iterator it = particles.begin();it != particles.end();++it )
    {
        (*it)->startFallOff(ofRandom(5.8));

    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    glPointSize(dotSize);

    vbo.setVertexData (&vboPoints[0], (int)vboPoints.size(), GL_DYNAMIC_DRAW);
    vbo.setColorData(&vboColors[0], (int)vboColors.size(), GL_STATIC_DRAW);
    
    vbo.draw(GL_POINTS, 0, (int)vboPoints.size());
   
    ofSetColor(120);
    ofDrawBitmapString(ofToString(particles.size()) + " particles " +ofToString(ofGetFrameRate()) + " fps" , 10, 10);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    startParticles();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
