//
//  postProcessing.hpp
//  shaderExam
//
//  Created by Eoin Roe on 22/01/2020.
//

#ifndef postProcessing_hpp
#define postProcessing_hpp

#include <stdio.h>
#include "ofMain.h"

using namespace glm;

class PostProcessing
{
public:
    PostProcessing();
    void draw(const ofFbo &fbo);
    ofParameterGroup parameters;
private:
    array<bool, 7> triggered = {false};
    array<ofParameter<float>, 7> sliders;
    ofParameter<bool> depth;
    ofShader shader;
};

#endif /* postProcessing_hpp */
