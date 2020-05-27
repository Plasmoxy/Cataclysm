#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);
	ofSetCircleResolution(128);
	ofEnableSmoothing();
	ofSetFrameRate(120);

	sliderGroup.setName("sliders");
	sliderGroup.add(intSlider.set("resolution", 3, 3, 64));
	sliderGroup.add(floatSlider.set("radius", 0.5f, 0.0f, 100.0f));
	gui.setup(sliderGroup);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetCircleResolution(intSlider);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 255, 230);

	ofDrawLine(0, 0, mx, my);
	ofDrawCircle(mx, my, floatSlider);

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case ' ':
			screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			screenshot.save("screen_" + ofToString(frame, 3, '0') + ".png");
			frame++;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mx = x;
	my = y;
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
