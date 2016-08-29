//
//  Brush.cpp
//  FluidSym
//
//  Created by David Crooks on 23/08/2016.
//
//
#include "ofApp.h"
#include "Brush.hpp"

int mouseX;
int mouseY;
int lastMouseX;
int lastMouseY;

void Brush::setup(){
    image.load("brush.png");
}

void Brush::update(){
    if(false) {
        int dx = lastMouseX - mouseX;
        int dy = lastMouseY - mouseY;
        double length = sqrt(dx*dx +dy*dy);
        int n_draw_points = floor(length/3);
        
        ofVec2f startPoint = ofVec2f(lastMouseX, lastMouseY);
        ofVec2f endPoint = ofVec2f(mouseX, mouseY);
        ofVec2f v = (endPoint-startPoint)/n_draw_points ;
        
        for(int i = 1; i <= n_draw_points; i++){
            ofVec2f p = startPoint + i*v;
            paintPoints.push_back(p);
        }
    }
}

void Brush::draw(){
    if(brushDown) {

        int dx = lastMouseX - mouseX;
        int dy = lastMouseY - mouseY;
        double length = sqrt(dx*dx +dy*dy);
        int n_draw_points = floor(length/3);
        
        ofVec2f startPoint = ofVec2f(lastMouseX, lastMouseY);
        ofVec2f endPoint = ofVec2f(mouseX, mouseY);
        ofVec2f v = (endPoint-startPoint)/n_draw_points ;
        
        for(int i = 1; i <= n_draw_points; i++){
            ofVec2f p = startPoint + i*v;
            int brushImageX = p.x - size * 0.5;
            int brushImageY = p.y - size * 0.5;
            ofSetColor(paintColor);
            image.draw(brushImageX, brushImageY, size, size);
        }
        
        /*
        for(int i = 0; i < paintPoints.size(); i++){
            ofVec2f p = paintPoints[i];
            int brushImageX = p.x - size * 0.5;
            int brushImageY = p.y - size * 0.5;
            ofSetColor(paintColor);
            image.draw(brushImageX, brushImageY, size, size);
        }
        paintPoints.clear();
         */
    }
}


void Brush::mouseDragged(int x, int y, int button){
   
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    mouseX = x;
    mouseY = y;
}

void Brush::mousePressed(int x, int y, int button){
    mouseX = x;
    mouseY = y;
    brushDown = true;
}

void Brush::mouseReleased(int x, int y, int button){
    brushDown = false;
}

