#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("OpenFrameworks example in vs2019");
	gui.setup();
	gui.add(radius.setup("radius", 140, 10, 300));
	gui.add(l1.setup("", "Selekt kolore:"));
	gui.add(colorSlider.setup(ofColor(1.0f, 0.0f, 0.0f)));

	ofSetVerticalSync(true);
	cam.setDistance(160);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofSetColor(colorSlider);
	//ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, (float)radius);

	/*
	ofEnableDepthTest();
	ofPushMatrix();
		camera.begin();
		light.enable();
		ofSphere(ofGetWidth() / 2, ofGetHeight() / 2, -200, 100);
		light.disable();
		camera.end();
	ofPopMatrix();
	ofDisableDepthTest();

	gui.draw();
	*/

	ofEnableDepthTest();
	cam.begin();
	ofSetColor(colorSlider);
	ofNoFill();
	ofDrawBox(30);
	cam.end();

	ofDisableDepthTest();
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
