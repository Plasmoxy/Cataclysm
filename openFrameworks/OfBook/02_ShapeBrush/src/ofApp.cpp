#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
		ofSetRectMode(OF_RECTMODE_CENTER);

		int numRects = 5;
		for (int r = 0; r < numRects; r++) {
			ofSetColor(0, ofRandom(50, 255), ofRandom(50, 255));
			float w = ofRandom(0, 2);
			float h = ofRandom(0, 2);
			float dx = ofRandom(-30, 30);
			float dy = ofRandom(-30, 30);

			ofDrawRectangle(
				ofGetMouseX() + dx,
				ofGetMouseY() + dy,
				w, h
			);
		}
	}
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
