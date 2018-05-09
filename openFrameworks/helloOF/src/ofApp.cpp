#include "ofApp.h"
#include <iostream>
#include <string>
#include <sstream>
#include "objects.h"

// random background on start
ofApp::ofApp() :
	bgColor(30),
	rectColor(getRandomColor()),
	rectColorTimer(0), // !!!! not object, will not be initialized by definition
	e1(500, 50),
	v1(200, 50),
	gravity(0, 100),
	gravityOn(false)
{}

//--------------------------------------------------------------
void ofApp::setup() {

	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetWindowTitle("helloOF - Plasmoxy");
	ofSetFrameRate(60);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofBackground(bgColor);

	e1.color = ofColor(0, 255, 0);
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
	updateMouse();

	double dt = ofGetLastFrameTime(); // in milliseconds
	updateRectColorTimer(dt);

	// calculate velocity to mouse
	ofVec2f vm = mouse - v1.pos;
	vm.normalize();
	vm *= 200; // 200 px per sec ( can go against gravity )

	// update vehicle
	v1.desVel = vm;
	if (gravityOn) v1.applyForce(gravity);
	v1.update(dt);
	v1.draw();

	// update entity
	if (gravityOn) e1.applyForce(gravity);
	e1.update(dt);
	e1.draw();

	// setup text
	stringstream stext;
	stext << "Hello openFrameworks !!!" << endl;
	stext << "Click to toggle gravity." << endl;
	stext << "Gravity Force = " << gravityOn << endl;
	stext << "desired velocity = " << vm.x << " " << vm.y << endl;
	string text = stext.str();

	// draw text
	ofDrawBitmapString(text, 20, 20);


	// draw mouse rectangle
	ofPushStyle();
	ofSetColor(rectColor);
	ofDrawRectangle(mouse.x, mouse.y, 10, 10);
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

		rectColor.set(getRandomColor()); // change color

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
	gravityOn = !gravityOn;
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
