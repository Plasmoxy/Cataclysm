#include "ofApp.h"

int t = 0;

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

		t++;
		float r = 20 * (t / 60.0f);

		int numRects = 20;
		for (int i = 0; i < numRects; i++) {
			ofSetColor(0, ofRandom(50, 255), ofRandom(50, 255));
			float w = ofRandom(0.0f, 1.0f);
			float h = ofRandom(0, 3);
			float dx = ofRandom(-r, r);
			float dy = ofRandom(-r, r);

			ofDrawCircle(
				ofGetMouseX() + dx,
				ofGetMouseY() + dy,
				w
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
