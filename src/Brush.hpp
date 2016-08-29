//
//  Brush.hpp
//  FluidSym
//
//  Created by David Crooks on 23/08/2016.
//
//

#ifndef Brush_hpp
#define Brush_hpp

#include <stdio.h>
#include "ofApp.h"
class Brush {
    
public:
    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
   // ofFbo *fbo;
    vector<ofVec3f> paintPoints;
    bool brushDown=false;
    ofImage image;
    double size = 100;
    ofColor paintColor = ofColor(0,0,0,255);
};
#endif /* Brush_hpp */
