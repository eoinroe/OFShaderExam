//
//  render.hpp
//  shaderExam
//
//  Created by Eoin Roe on 23/01/2020.
//

#ifndef render_hpp
#define render_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Render
{
public:
    Render();
    void draw();
    array<ofParameterGroup, 3> parameters;
private:
    ofShader shader;
    ofEasyCam camera;
    
    ofMesh mesh;
    ofTexture texture;
    ofxAssimpModelLoader model;
    
    ofParameter<bool> lightingEnabled = false;
    ofParameter<bool> wireframe = false;
    
    ofParameter<ofColor> lightColor;
    
    array<ofParameter<float>, 3> sliders;
};

#endif /* render_hpp */
