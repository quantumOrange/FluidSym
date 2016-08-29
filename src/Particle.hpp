//
//  Partical.hpp
//  FluidSym
//
//  Created by David Crooks on 24/08/2016.
//
//

#ifndef Particle_hpp
#define Particle_hpp
#include "ofApp.h"
#include <stdio.h>
class Particle {
    public:
        void setup(int _width, int _height,double _mass,double _flowPerturbationAmount,double drag);
        void update(ofVec2f force);
        void draw();
    
        ofVec2f position;
        ofVec2f diffPosition;
        ofVec2f lastPosition;
        ofVec2f velocity;
        
        double mass;
        double dragCoeffiecent;
        double flowPerturbationAmount;
        ofImage image;
        double size = 100;
        ofColor color = ofColor(255,0,0,255);
    
        int width;
        int height;
    
        double startHue;
        double noiseStartTime;
    
    private:
        void drawSeamless(ofVec2f drawPoint,double drawSize);
        ofVec2f flowPerturbation();
        ofVec2f drag();
    
        double varyingSize;
};
#endif /* Particle_hpp */
