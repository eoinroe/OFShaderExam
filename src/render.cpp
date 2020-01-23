//
//  render.cpp
//  shaderExam
//
//  Created by Eoin Roe on 23/01/2020.
//

#include "render.hpp"

//--------------------------------------------------------------
Render::Render()
{
    parameters[0].setName("Tessellation");
    parameters[0].add(wireframe.set("Wireframe Mode", false));
    
    parameters[1].setName("Lighting");
    parameters[1].add(lightingEnabled.set("Directional Light", false));
    parameters[1].add(lightColor.set("Light Color", ofColor(255)));
    
    parameters[2].setName("Vertex Animation");
    parameters[2].add(sliders[0].set("Chubby", 0, 0, 20));
    parameters[2].add(sliders[1].set("Waviness", 0, 0, 75));
    parameters[2].add(sliders[2].set("Twist Factor", 0.0f, 0.0f, 1.0f));
    
    // Tessellation has been applied in Blender to improve the appearance
    // of the model when mesh deformation is applied in the vertex shader
    model.loadModel("pikachu.obj");
    mesh = model.getMesh(0);
    
    // Using normalized texture coordinates
    ofDisableArbTex();
    ofLoadImage(texture, "pikachu.png");
    
    shader.load("base");
    
    // Move camera forward a little so depth texture is visible
    camera.setPosition(0, 0, 525);
}

//--------------------------------------------------------------
void Render::update()
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
        }
    }
    
    if (sliders[1] > 0.0f){
        if (!triggered[1]){
            triggered[1] = true;
            
            // Set all other sliders to 0
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 1){
                    sliders[i] = 0.0f;
                    triggered[i] = false;
                }
            }
        }
    }
    
    if (sliders[2] > 0.0f){
        if (!triggered[2]){
            triggered[2] = true;
            
            // Set all other sliders to 0
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 2){
                    sliders[i] = 0.0f;
                    triggered[i] = false;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void Render::draw()
{
    ofEnableDepthTest();
    camera.begin();
    
    ofBackground(255);
    
    shader.begin();
    shader.setUniform1f( "size", sliders[0]);
    shader.setUniform1f( "waviness", sliders[1] );
    shader.setUniform1f( "twistFactor", sliders[2] );
    shader.setUniform1i( "lightingEnabled", lightingEnabled );
    shader.setUniformTexture( "tex0", texture, 0 );
    
    if (lightingEnabled)
        shader.setUniform3f( "lightColor", float(lightColor->r) / 255.0f, float(lightColor->g) / 255.0f, float(lightColor->b) / 255.0f );
    
    ofPushMatrix();
    ofScale(50);
    ofTranslate(-0.4, -6);
    
    if (!wireframe) {
        mesh.draw();
    } else {
        // You can see how much tessellation has been applied to the model in wireframe mode
        mesh.drawWireframe();
    }
    
    ofPopMatrix();
    
    shader.end();
    
    camera.end();
    ofDisableDepthTest();
}
