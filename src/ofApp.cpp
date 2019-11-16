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
    
    crash.load("base.vert", "crash.frag");
    chromaticAbberation.load("base.vert", "chromatic.frag");
    wavy.load("base.vert", "vague.frag");
    
    
    gui.setup();
       
    gui.add(wireframe.set("Wireframe Mode", false));
//    gui.add(chromatic.setup("Chromatic Abberation"));
//    gui.add(crash.setup("Crash"));
//    gui.add(wavy.setup("Wavy"));
    
    gui.add(toggle[0].set("Chromatic Abberation", false));
    gui.add(toggle[1].set("Crash", false));
    gui.add(toggle[2].set("Wavy", false));
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
//        for (int i = 0; i < toggle.size(); ++i){
//            if (i != 0){
//                toggle[i] = false;
//            }
//        }
        
        if (set == false){
            toggle[1] = false;
            toggle[2] = false;
            toggle[3] = false;
        }
        
        
        chromaticAbberation.begin();
        chromaticAbberation.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        chromaticAbberation.setUniformTexture( "tex0", fbo.getTexture(), 0);
        fbo.draw(0, 0);
        chromaticAbberation.end();
        
        set = true;
    }
    
    if (toggle[1]){
//        for (int i = 0; i < toggle.size(); ++i){
//            if (i != 1){
//                toggle[i] = false;
//            }
//        }
        
        //toggle[0] = false;
        //toggle[2] = false;
        //toggle[3] = false;
        
        crash.begin();
        crash.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        crash.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        crash.end();
    }
    
    if (toggle[2]){
//        for (int i = 0; i < toggle.size(); ++i){
//            if (i != 2){
//                toggle[i] = false;
//            }
//        }
        
        //toggle[0] = false;
        //toggle[1] = false;
        //toggle[3] = false;
        
        wavy.begin();
        wavy.setUniform2f( "u_resolution", vec2(ofGetWidth(), ofGetHeight()) );
        wavy.setUniformTexture( "tex0", fbo.getTexture(), 0 );
        fbo.draw(0, 0);
        wavy.end();
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
