#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    
    ofFboSettings settings;
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
    
    //could write a loop that sets up all the vertex shaders from file?
    crash.setupShaderFromFile(GL_VERTEX_SHADER, "post.vert");
    crash.setupShaderFromFile(GL_FRAGMENT_SHADER, "crash.frag");
    
    crash.bindDefaults();
    crash.linkProgram();
    
    
    // Load all the shaders in setup for improved efficiency
    //crash.load("base.vert", "crash.frag");
    chromaticAbberation.load("post.vert", "chromatic.frag");
    wavy.load("post.vert", "vague.frag");
    pixelated.load("post.vert", "pixelated.frag");
    depth.load("post.vert", "depth.frag");
    
    gui.setup();
       
    gui.add(wireframe.set("Wireframe Mode", false));
    gui.add(toggle[0].set("Chromatic Abberation", false));
    gui.add(toggle[1].set("Crash", false));
    gui.add(toggle[2].set("Wavy", false));
    gui.add(toggle[3].set("Pixelated", false));
    gui.add(toggle[4].set("Depth Texture", false));
    gui.add(color.set("Background Color", ofColor(255)));
    gui.add(twistFactor.set("Twist", 0, -1, 1));
    gui.add(size.set("Chubby", 0, 0, 20));
}

//--------------------------------------------------------------
void ofApp::update(){
    // Start fbo then begin the camera!
    fbo.begin();
    
    ofEnableDepthTest();
    camera.begin();
    
    // Seems like it is important to do this here - but not necessarily in setup!
    ofClear(0, 0, 0, 255);
    
    ofBackground(color);
    
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
        depth.setUniformTexture("tex0", fbo.getDepthTexture(), 1);
        fbo.draw(0, 0);
        depth.end();
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
