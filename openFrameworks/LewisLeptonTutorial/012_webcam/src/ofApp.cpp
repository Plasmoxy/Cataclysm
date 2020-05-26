#include "ofApp.h"

ofVideoGrabber cam;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("SEBU STRONK!");
	cam.setup(640, 480);
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	int n = 5;
	int d = ofGetWindowWidth() / n;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cam.draw(x*d, y*d, d, d);
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
