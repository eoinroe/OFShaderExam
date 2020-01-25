//
//  postProcessing.cpp
//  shaderExam
//
//  Created by Eoin Roe on 22/01/2020.
//

#include "postProcessing.hpp"

//--------------------------------------------------------------
PostProcessing::PostProcessing()
{
    parameters.setName("Post Processing");
    parameters.add(depth.set("Depth Texture", false));
    parameters.add(sliders[0].set("Chromatic Abberration", 0.0f, 0.0f, 0.01f));
    parameters.add(sliders[1].set("Crash", 0.0f, 0.0f, 0.1f));
    parameters.add(sliders[2].set("Wavy", 0.0f, 0.0f, 0.1f));
    parameters.add(sliders[3].set("Pixelated", 0.0f, 0.0f, 20.0f));
    parameters.add(sliders[4].set("Threshold", 0.0f, 0.0f, 1.0f));
}

//--------------------------------------------------------------
void PostProcessing::draw(const ofFbo &fbo)
{
    if (sliders[0] > 0.0f){
        if (!triggered[0]){
            triggered[0] = true;
            
            // Set all other sliders to 0
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 0){
                    sliders[i] = 0.0f;
                    triggered[i] = false;
                }
            }
            
            cout << "Chromatic abberation" << endl;
            shader.load("post.vert", "chromatic.frag");
        }
        
        shader.begin();
        shader.setUniform1f( "scale", sliders[0].get() );
        shader.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        shader.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        shader.end();
    }
    
    if (sliders[1] > 0.0f){
        if (!triggered[1]){
            triggered[1] = true;
            
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 1){
                    sliders[i] = 0.0f;
                    triggered[i] = false;
                }
            }
            
            cout << "Crash" << endl;
            shader.load("post.vert", "crash.frag");
        }
                
        shader.begin();
        shader.setUniform1f( "level", sliders[1].get() );
        shader.setUniform2f( "lod", vec2(ofGetWidth(), ofGetHeight()) * sliders[1].get() );
        shader.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        shader.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        shader.end();
    }
    
    if (sliders[2] > 0.0f){
        if (!triggered[2]){
            triggered[2] = true;
            
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 2){
                    sliders[i] = 0.0f;
                    triggered[i] = false;
                }
            }
            
            cout << "Wavy" << endl;
            shader.load("post.vert", "vague.frag");
        }
        
        shader.begin();
        shader.setUniform1f( "level", sliders[2].get() );
        shader.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        shader.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        shader.end();
    }
    
    if (sliders[3] > 0.0f){
        if (!triggered[3]){
            triggered[3] = true;
            
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 3){
                    sliders[i] = false;
                    triggered[i] = false;
                }
            }
            
            cout << "Pixelated" << endl;
            shader.load("post.vert", "pixelated.frag");
        }
        
        shader.begin();
        shader.setUniform1f( "level", sliders[3].get() );
        shader.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        shader.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        shader.end();
    }
    
    if (sliders[4] > 0.0f){
        if (!triggered[4]){
            triggered[4] = true;
            
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 4){
                    sliders[i] = 0.0f;
                    triggered[i] = false;
                }
            }
            
            cout << "Threshold" << endl;
            shader.load("post.vert", "threshold.frag");
        }
        
        float threshold = ofMap(sliders[4].get(), 0.0f, 1.0f, 0.5f, 0.75f);
        
        shader.begin();
        shader.setUniform1f( "threshold", threshold );
        shader.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        shader.end();
    }
    
    if (depth){
        if (!triggered[5]){
            triggered[5] = true;
            
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 5){
                    sliders[i] = 0.0f;
                    triggered[i] = false;
                }
            }
            
            cout << "Depth texture" << endl;
            shader.load("post.vert", "depth.frag");
        }
        
        shader.begin();
        shader.setUniformTexture( "tex0", fbo.getDepthTexture(), 1 );    // Make sure this is 1!
        fbo.draw(0, 0);
        shader.end();
    }
    
    if ( std::none_of(sliders.begin(), sliders.end(), [](float v) { return v > 0.0f; }) && !depth ) {
        fbo.draw(0, 0);
    }
}
