#include "ofApp.h"
#include <iostream>


// random background on start
ofApp::ofApp() :
	bgColor(30),
	rectColor(getRandomColor()),
	rectColorTimer(0)
{

}

//--------------------------------------------------------------
void ofApp::setup() {

	//ofEnableSmoothing();
	//ofEnableAlphaBlending();
	ofSetWindowTitle("helloOF - Plasmoxy");
	ofSetFrameRate(60);
	ofSetRectMode(OF_RECTMODE_CENTER);

	ofBackground(bgColor);




}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	updateMouse();

	double dt = ofGetLastFrameTime(); // in milliseconds
	updateRectColorTimer(dt);
	
	

	ofPushStyle();
	ofSetColor(rectColor);
	ofDrawRectangle(mouse.x, mouse.y, 30, 30);
	ofPopStyle();
}


// CUSTOM

void ofApp::updateMouse() {
	mouse.x = ofGetMouseX();
	mouse.y = ofGetMouseY();
}

ofColor ofApp::getRandomColor() {
	return ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void ofApp::updateRectColorTimer(double dt) {
	rectColorTimer += dt;
	
	if (rectColorTimer > 1.0) { // after one second

		rectColor = getRandomColor(); // change color

		rectColorTimer = 0; // reset timer
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	cout << "MOUSE PRESSED" << endl;

	rectColor = getRandomColor();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
