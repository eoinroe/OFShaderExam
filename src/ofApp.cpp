#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    
    ofFboSettings settings;
    settings.internalformat = GL_RGB32F;
    settings.width = ofGetWidth();
    settings.height = ofGetHeight();
    settings.useDepth = true;
    settings.depthStencilAsTexture = true;

    fbo.allocate(settings);
    
    fbo.begin();
    ofClear(0, 0, 0);
    ofClearAlpha();
    fbo.end();
    
    // Tessellation has been applied in Blender to improve the appearance
    // of the model when mesh deformation is applied in the vertex shader
    model.loadModel("pikachu.obj");
    mesh = model.getMesh(0);
    
    ofLoadImage(texture, "pikachu.png");
    
    render.load("base");
    
    parameters[0].setName("Settings");
    parameters[0].add(wireframe.set("Wireframe Mode", false));
    parameters[0].add(light.set("Directional Light", false));
    parameters[0].add(lightColor.set("Light Color", ofColor(255)));
    
    parameters[1].setName("Post Processing");
    parameters[1].add(depth.set("Depth Texture", false));
    parameters[1].add(sliders[0].set("Chromatic Abberration", 0.0f, 0.0f, 0.01f));
    parameters[1].add(sliders[1].set("Crash", 0.0f, 0.0f, 0.1f));
    parameters[1].add(sliders[2].set("Wavy", 0.0f, 0.0f, 0.1f));
    parameters[1].add(sliders[3].set("Pixelated", 0.0f, 0.0f, 20.0f));
    parameters[1].add(sliders[4].set("Threshold", 0.0f, 0.0f, 1.0f));
    
    parameters[2].setName("Vertex Animation");
    parameters[2].add(twistFactor.set("Twist Factor", 0, -1, 1));
    parameters[2].add(size.set("Chubby", 0, 0, 20));
    parameters[2].add(waviness.set("Waviness", 0, 0, 75));
    
    parameters[0].add(parameters[1]);
    parameters[0].add(parameters[2]);
    
    gui.setup(parameters[0]);
    
    // Move camera forward a little so depth texture is visible
    camera.setPosition(0, 0, 525);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Start fbo then begin the camera!
    fbo.begin();
    
    ofEnableDepthTest();
    camera.begin();
    
    // Seems like it is important to do this here - but not necessarily in setup!
    ofClear(0, 0, 0, 255);
    
    ofBackground(255);
    
    render.begin();
    render.setUniform1f( "size", size);
    render.setUniform1f( "waviness", waviness );
    render.setUniform1f( "twistFactor", twistFactor );
    render.setUniform1i( "lightingEnabled", light );
    render.setUniformTexture( "tex0", texture, 0 );
    
    if (light)
        render.setUniform3f( "lightColor", float(lightColor->r) / 255.0f, float(lightColor->g) / 255.0f, float(lightColor->b) / 255.0f );
    
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
    
    render.end();
    
    camera.end();
    ofDisableDepthTest();
    
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (sliders[0] > 0.0f){
        if (!triggered[0]){
            triggered[0] = true;
            
            // Set all other toggles to false
            for (int i = 0; i < sliders.size(); ++i){
                if (i != 0){
                    sliders[i] = 0.0f;
                    triggered[i] = false;
                }
            }
            
            cout << "Chromatic abberation" << endl;
            postProcessing.load("post.vert", "chromatic.frag");
        }
        
        postProcessing.begin();
        postProcessing.setUniform1f( "scale", sliders[0].get() );
        postProcessing.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
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
            postProcessing.load("post.vert", "crash.frag");
        }
                
        postProcessing.begin();
        postProcessing.setUniform1f( "level", sliders[1].get() );
        postProcessing.setUniform2f( "lod", vec2(ofGetWidth(), ofGetHeight()) * sliders[1].get() );
        postProcessing.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
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
            postProcessing.load("post.vert", "vague.frag");
        }
        
        postProcessing.begin();
        postProcessing.setUniform1f( "level", sliders[2].get() );
        postProcessing.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
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
            postProcessing.load("post.vert", "pixelated.frag");
        }
        
        postProcessing.begin();
        postProcessing.setUniform1f( "level", sliders[3].get() );
        postProcessing.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
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
            postProcessing.load("post.vert", "grayscale.frag");
        }
        
        postProcessing.begin();
        postProcessing.setUniform1f( "threshold", sliders[4].get() );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
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
            postProcessing.load("post.vert", "depth.frag");
        }
        
        postProcessing.begin();
        postProcessing.setUniformTexture( "tex0", fbo.getDepthTexture(), 1 );    // Make sure this is 1!
        fbo.draw(0, 0);
        postProcessing.end();
    }
    
    if ( std::none_of(sliders.begin(), sliders.end(), [](float v) { return v > 0.0f; }) && !depth ) {
        fbo.draw(0, 0);
    }
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
