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
    
    gui.setup();
       
    gui.add(wireframe.set("Wireframe Mode", false));
    gui.add(light.set("Directional Light", false));
    gui.add(lightColor.set("Light Color", ofColor(255)));
    gui.add(toggle[0].set("Chromatic Abberation", false));
    gui.add(toggle[1].set("Crash", false));
    gui.add(toggle[2].set("Wavy", false));
    gui.add(toggle[3].set("Pixelated", false));
    gui.add(toggle[4].set("Depth Texture", false));
    gui.add(toggle[5].set("Grayscale", false));
    gui.add(toggle[6].set("Overlay", false));
    gui.add(overlayColor.set("Overlay Color", ofColor(255)));
    gui.add(twist.set("Twist", false));
    gui.add(twistFactor.set("Twist Factor", 0, -1, 1));
    gui.add(size.set("Chubby", 0, 0, 20));
    
    // Move camera forward a little so depth texture is visible
    camera.setPosition(0, 0, 525);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!twist)
        twistFactor = 0.0f;
    
    // Find a way to load the shaders only if the boolean has changed?
    if (light) {
        render.load("light");
    } else {
        render.load("base");
    }
    
    // Start fbo then begin the camera!
    fbo.begin();
    
    ofEnableDepthTest();
    camera.begin();
    
    // Seems like it is important to do this here - but not necessarily in setup!
    ofClear(0, 0, 0, 255);
    
    ofBackground(255);
    
    render.begin();
    render.setUniform1f( "size", size);
    render.setUniform1f( "twistFactor", twistFactor );
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
    if (toggle[0]){
        if (!triggered[0]){
            triggered[0] = true;
            
            for (int i = 0; i < toggle.size(); ++i){
                if (i != 0){
                    toggle[i] = false;
                    triggered[i] = false;
                }
            }
        }
      
        postProcessing.load("base.vert", "chromatic.frag");
                
        postProcessing.begin();
        postProcessing.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
        
    }
    
    if (toggle[1]){
        if (!triggered[1]){
            triggered[1] = true;
            
            for (int i = 0; i < toggle.size(); ++i){
                if (i != 1){
                    toggle[i] = false;
                    triggered[i] = false;
                }
            }
        }
        
        postProcessing.load("base.vert", "crash.frag");
                
        postProcessing.begin();
        postProcessing.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
    }
    
    if (toggle[2]){
        if (!triggered[2]){
            triggered[2] = true;
            
            for (int i = 0; i < toggle.size(); ++i){
                if (i != 2){
                    toggle[i] = false;
                    triggered[i] = false;
                }
            }
        }
        
        postProcessing.load("base.vert", "vague.frag");
        
        postProcessing.begin();
        postProcessing.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
    }
    
    if (toggle[3]){
        if (!triggered[3]){
            triggered[3] = true;
            
            for (int i = 0; i < toggle.size(); ++i){
                if (i != 3){
                    toggle[i] = false;
                    triggered[i] = false;
                }
            }
        }
        
        postProcessing.load("base.vert", "pixelated.frag");
        
        postProcessing.begin();
        postProcessing.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
    }
    
    if (toggle[4]){
        if (!triggered[4]){
            triggered[4] = true;
            
            for (int i = 0; i < toggle.size(); ++i){
                if (i != 4){
                    toggle[i] = false;
                    triggered[i] = false;
                }
            }
        }
        
        postProcessing.load("base.vert", "depth.frag");
        
        postProcessing.begin();
        postProcessing.setUniformTexture( "tex0", fbo.getDepthTexture(), 1 );    // Make sure this is 1!
        fbo.draw(0, 0);
        postProcessing.end();
    }
    
    if (toggle[5]){
        if (!triggered[5]){
            triggered[5] = true;
            
            for (int i = 0; i < toggle.size(); ++i){
                if (i != 5){
                    toggle[i] = false;
                    triggered[i] = false;
                }
            }
        }
        
        postProcessing.load("base.vert", "grayscale.frag");
        
        postProcessing.begin();
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        postProcessing.end();
    }
    
    // This is most effective when the phong shader is being used
    if (toggle[6]){
        if (!triggered[6]){
            triggered[6] = true;
            
            for (int i = 0; i < toggle.size(); ++i){
                if (i != 6){
                    toggle[i] = false;
                    triggered[i] = false;
                }
            }
        }
        
        postProcessing.load("base.vert", "overlay.frag");
        
        postProcessing.begin();
        postProcessing.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        postProcessing.setUniform3f( "tint", float(overlayColor->r) / 255.0f, float(overlayColor->g) / 255.0f, float(overlayColor->b) / 255.0f );
        fbo.draw(0, 0);
        postProcessing.end();
    }
    
    if ( std::none_of(toggle.begin(), toggle.end(), [](bool v) { return v; }) ) {
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
