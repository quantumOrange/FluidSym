//
//  FluidSym.hpp
//  FluidSym
//
//  Created by David Crooks on 20/08/2016.
//
//

#ifndef FluidSym_hpp
#define FluidSym_hpp

#include <stdio.h>
#include "ofApp.h"
class FluidSym  {
    
    public:
        void setup();
        void update();
        void draw();
        void draw(int x,int y);
        ofFbo *fbo = new ofFbo();
    
    
        double advectionRate = 10.0;
      //  double diffusionnRate = 0.0;
        double flowEvolutionRate = 0.05;
        double flowScale = 0.3;
    
        int width = 0;
        int height = 0;
    
        bool seamless = true;
    
    private:
        ofImage startImage;
        ofShader shader;
        ofFbo *fbo2 = new ofFbo();
    
};
#endif /* FluidSym_hpp */
