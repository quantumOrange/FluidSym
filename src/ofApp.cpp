#include "ofApp.h"
#include "FluidSym.hpp"
#include "Brush.hpp"
#include "Particle.hpp"

Brush *brush = new Brush();
FluidSym *fluid = new FluidSym();
//Particle *particle = new Particle();
vector<Particle> inkSourses (5,Particle());
bool twoByTwo = false;

//--------------------------------------------------------------

void ofApp::setup(){
    ofSetFrameRate(60);
    if (twoByTwo){
        fluid->width = ofGetWidth()/2;
        fluid->height = ofGetHeight()/2;
    }
    
    fluid->setup();
    brush->setup();
   // particle->setup(fluid->width,fluid->height,1.0,20.0,0.001);
    for_each(inkSourses.begin(), inkSourses.end(),[](Particle& p) {p.setup(fluid->width,fluid->height,1.0,40.0,0.005);} );
    
    //a large splash of white
    inkSourses[0].color.setSaturation(0);
    inkSourses[0].size = 150;
    
    
    //Dark complimentary color for contrast
    inkSourses[1].color.setBrightness(100);
    inkSourses[1].startHue = 195; //default start color averages at 15, so 180+15 is the complimentary color.
    
}

//--------------------------------------------------------------
void ofApp::update(){
    fluid->update();
    brush->update();
    for_each(inkSourses.begin(), inkSourses.end(),[](Particle& p) {p.update(ofVec2f());} );
   // particle->update(ofVec2f(0.0,0.0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    fluid->draw();
    
    fluid->fbo->begin();
    brush->draw();
    //particle->draw();
    for_each(inkSourses.begin(), inkSourses.end(),[](Particle& p) {p.draw();} );
    fluid->fbo->end();
    
    if (twoByTwo){
        fluid->draw(0,fluid->height);
        fluid->draw(fluid->width,0);
        fluid->draw(fluid->width,fluid->height);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
 cout << ofGetFrameRate() << endl;
    cout << key << endl;
    double ds = 0.05;
    
    if (key ==97) {
        fluid->flowScale += ds;
    }
    else if (key == 122){
        fluid->flowScale -= ds;
    }
    
    switch(key) {
        case 49:// 1
            brush->paintColor = ofColor(255,255,255,255);
            break;
        case 50:// 2
            brush->paintColor = ofColor(0,0,0,255);
            break;

        case 51:// 3
            brush->paintColor = ofColor(255,255,0,255);
            break;
        case 52:// 4
            brush->paintColor = ofColor(0,0,255,255);
            break;

        default:
            break;
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
    brush ->  mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    brush -> mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    brush->mouseReleased(x, y, button);
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
