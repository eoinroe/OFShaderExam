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
    
    //filters.allocate(settings);
    fbo.allocate(settings);
    
    fbo.begin();
    ofClear(0, 0, 0);
    ofClearAlpha();
    fbo.end();
    
    // Tessellation has been applied in Blender to improve the appearance of the model
    // when mesh deformation is applied in the vertex shader
    model.loadModel("pikachu.obj");
    mesh = model.getMesh(0);
    
    ofLoadImage(texture, "pikachu.png");
    
    render.load("base");
    //postProcessing.load("base.vert", "crash.frag");
    
    // Load all the shaders in setup for improved efficiency
    crash.load("base.vert", "crash.frag");
    chromaticAbberation.load("post.vert", "chromatic.frag");
    wavy.load("post.vert", "vague.frag");
    pixelated.load("post.vert", "pixelated.frag");
    depth.load("post.vert", "depth.frag");
    gray.load("post.vert", "grayscale.frag");
    overlayShader.load("post.vert", "overlay.frag");
    
    gui.setup();
       
    gui.add(wireframe.set("Wireframe Mode", false));
    gui.add(toggle[0].set("Chromatic Abberation", false));
    gui.add(toggle[1].set("Crash", false));
    gui.add(toggle[2].set("Wavy", false));
    gui.add(toggle[3].set("Pixelated", false));
    gui.add(toggle[4].set("Depth Texture", false));
    gui.add(toggle[5].set("Grayscale", false));
    gui.add(toggle[6].set("Overlay", false));
    gui.add(color.set("Overlay Color", ofColor(255)));
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
    
    ofPushMatrix();
    ofScale(50);
    ofTranslate(-0.4, -6);
    
    if (!wireframe) {
        mesh.draw();
    } else {
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
                
        chromaticAbberation.begin();
        chromaticAbberation.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        chromaticAbberation.setUniformTexture( "tex0", fbo.getTexture(), 0);
        fbo.draw(0, 0);
        chromaticAbberation.end();
        
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
                
        crash.begin();
        crash.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        crash.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        crash.end();
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
        
        wavy.begin();
        wavy.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        wavy.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        wavy.end();
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
        
        pixelated.begin();
        pixelated.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        pixelated.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        pixelated.end();
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
        
        depth.begin();
        depth.setUniformTexture( "tex0", fbo.getDepthTexture(), 1 );    // Make sure this is 1!
        fbo.draw(0, 0);
        depth.end();
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
        
        gray.begin();
        gray.setUniformTexture( "tex0", fbo.getTexture(), 0);
        fbo.draw(0, 0);
        gray.end();
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
        
        // Get current value of ofxColorSlider
        overlayColor = color;

        overlayShader.begin();
        overlayShader.setUniformTexture( "tex0", fbo.getTexture(), 0);
        overlayShader.setUniform3f( "tint", float(overlayColor.r) / 255.0f, float(overlayColor.g) / 255.0f, float(overlayColor.b) / 255.0f );
        fbo.draw(0, 0);
        overlayShader.end();
        
        
        // Cast to a float and then divide by a float, rather than dividing
        // first and then casting the result of the division to a float
        cout << to_string(float(overlayColor.r) / 255.0f) << endl;
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
