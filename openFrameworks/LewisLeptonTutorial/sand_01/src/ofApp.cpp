#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);
	ofSetCircleResolution(128);
	ofEnableSmoothing();
	ofSetFrameRate(120);

	gui.setup();
	gui.add(intSlider.setup("int slider", 64, 0, 64));
	gui.add(floatSlider.setup("float slider", 0.5f, 0.0f, 1.0f));
	gui.add(toggle.setup("toggle", false));
	gui.add(button.setup("button"));
	gui.add(label.setup("label", "THIS IS LABEL XDXD"));
	gui.add(intField.setup("int field", 100, 0, 100));
	gui.add(floatField.setup("float field", 100.0, 0.0f, 100.0));
	gui.add(textField.setup("text field", "text"));
	gui.add(vec2Slider.setup("vec2 slider", ofVec2f(0, 0), ofVec2f(0,0), ofVec2f(ofGetWidth()), ofGetHeight()));
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 255, 230);
	ofSetCircleResolution(intSlider);

	ofDrawLine(0, 0, vec2Slider->x, vec2Slider->y);
	ofDrawCircle(vec2Slider->x, vec2Slider->y, 120);

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
