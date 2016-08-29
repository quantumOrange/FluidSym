//
//  FluidSym.cpp
//  FluidSym
//
//  Created by David Crooks on 20/08/2016.
//
//

#include "FluidSym.hpp"
#include "ofApp.h"




void FluidSym::setup(){
    if(seamless) {
        ofDisableArbTex();
        shader.load("fluid.vert","fluidSeamless.frag");
    }
    else {
        shader.load("fluid");
    }
    
    if(!width){
        width = ofGetWidth();
    }
    if(!height){
        height = ofGetHeight();
    }
    startImage.load("Pattern.jpg");
  
    
    
    fbo->allocate(width,height);
    fbo->begin();
        ofClear(255,255,255, 0);
      //  startImage.draw(0,0,width,height);
    fbo->end();
    
    fbo2->allocate(width,height);
    fbo2->begin();
        ofClear(255,255,255, 0);
       // startImage.draw(0,0,width,height);
    fbo2->end();
    
    
}

//--------------------------------------------------------------
void FluidSym::update(){
    //swap framebuffers
    //we're ping-ponging between framebuffers so we need to swap them around each frame.
    std::swap(fbo,fbo2);
    
    
    fbo->begin();
    shader.begin();
        shader.setUniform1f("time", flowEvolutionRate*ofGetElapsedTimef());
        shader.setUniform1f("advectionRate", advectionRate*ofGetLastFrameTime());
        shader.setUniform2f("size", width,height);
        shader.setUniform2f("inverseSize", 1.0/width,1.0/height);
    
        if(seamless){
            //we obtain seamless noise by embeddig a torus in 4-space and using noise4d.
            //we can tune the noise
            shader.setUniform2f("torusRadii", flowScale,flowScale);
            fbo2->getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
        }
        else {
            shader.setUniform1f("flowScale",flowScale);
        }

        fbo2->draw(0,0);
    shader.end();
    fbo->end();
    
    
}

//--------------------------------------------------------------
void FluidSym::draw(){
    fbo->draw(0,0);
}

void FluidSym::draw(int x,int y){
    fbo->draw(x,y);
}


