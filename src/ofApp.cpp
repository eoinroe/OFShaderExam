#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Using normalized texture coordinates
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
    
    // No need to clear the alpha channel since I'm using the GL_RGB32F format
    // ofClearAlpha();
    fbo.end();    
    
    parameters.setName("Settings");
    
    parameters.add(render.parameters[0]);
    parameters.add(render.parameters[1]);
    parameters.add(render.parameters[2]);
    parameters.add(postProcessing.parameters);
    
    gui.setup(parameters);
    
    gui.getGroup("Tessellation").minimize();
    gui.getGroup("Lighting").minimize();
    gui.getGroup("Vertex Animation").minimize();
    gui.getGroup("Post Processing").minimize();
}

//--------------------------------------------------------------
void ofApp::update(){
    render.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    
    // Seems like it is important to do this here - but not necessarily in setup!
    ofClear(0, 0, 0);
    
    render.draw();
    fbo.end();
    
    postProcessing.draw(fbo);
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
