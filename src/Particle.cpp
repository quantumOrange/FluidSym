//
//  Partical.cpp
//  FluidSym
//
//  Created by David Crooks on 24/08/2016.
//
//

#include "Particle.hpp"


void Particle::setup(int _width, int _height,double _mass, double _flowPerturbationAmount, double _drag){
    flowPerturbationAmount =_flowPerturbationAmount;
    dragCoeffiecent = _drag;
    width = _width;
    height = _height;
    mass = _mass;
    image.load("brush.png");
    position = ofVec2f(ofRandom(width), ofRandom(height));
    velocity = ofVec2f(ofRandom(width), ofRandom(height));
    lastPosition = position;
    
    startHue = ofRandom(30);
    noiseStartTime = ofRandom(5.0);
}

void Particle::update(ofVec2f appliedForce){
  //  cout << "flow: " << flowPerturbation() <<endl;
  //  cout << "drag: " << drag() << endl;
    double sizeRate = 0.1;
    varyingSize =  size*ofNoise(noiseStartTime + sizeRate*ofGetElapsedTimef());
    ofVec2f totalForce = appliedForce + flowPerturbation() + drag();
    
    double hueRate = 2.0;
    double hue = ofWrap(startHue+hueRate*ofGetElapsedTimef(),0,360);
    color.setHueAngle(hue);
    
    lastPosition = position;
    double dt = ofGetLastFrameTime();
    ofVec2f acceleration = totalForce/mass;
    
    velocity += acceleration *dt;
    position += velocity * dt;
    position.x = ofWrap(position.x, 0, width);
    position.y = ofWrap(position.y, 0, height);
    diffPosition = velocity * dt;
    
  //  cout << "p: " << position << endl;
  //  cout << "v: " << velocity << endl;
}


ofVec2f Particle::flowPerturbation() {
    double time = noiseStartTime + ofGetElapsedTimef();
    double x = position.x/width;
    double y =  position.y/height;
    double epsilon = 0.05;
    
    //derivitives of noise
    double dNdx = 0.5*(ofNoise(x+epsilon,y,time) - ofNoise(x-epsilon,y,time))/epsilon;
    double dNdy = 0.5*(ofNoise(x,y+epsilon,time) - ofNoise(x,y-epsilon,time))/epsilon;
    
    //curl of noise
    ofVec2f curlN = ofVec2f(dNdy, -dNdx);
    
    return curlN*flowPerturbationAmount;
}

ofVec2f Particle::drag() {
    double speed = velocity.length();
    ofVec2f v = velocity.getNormalized();
    
    return  - dragCoeffiecent * speed * speed * v ;
}


void Particle::draw(){
    double length = diffPosition.length();
    int n_draw_points = ceil(length/3);

    ofVec2f dp = diffPosition/n_draw_points ;

    for(int i = 1; i <= n_draw_points; i++){
        ofVec2f p = lastPosition + i*dp;
        drawSeamless(p,varyingSize);
    }
}

void Particle::drawSeamless(ofVec2f drawPoint,double drawSize) {
    ofVec2f p = ofVec2f();
    ofSetColor(color);
    
    for(int i = -1; i<=1 ;i++) {
        p.x = drawPoint.x + i*width;
        
        for(int j = -1; j<=1 ;j++) {
           
            p.y = drawPoint.y + j*height;
            int imageX = p.x - drawSize * 0.5;
            int imageY = p.y - drawSize * 0.5;
            
            image.draw(imageX, imageY, drawSize, drawSize);
        }
    }
}
