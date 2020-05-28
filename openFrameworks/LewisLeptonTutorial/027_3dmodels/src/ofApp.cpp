#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetGlobalAmbientColor(ofFloatColor::black);

	gui.setup();
	gui.add(
		lightPos.setup("light pos", ofVec3f(0, 0, 200), ofVec3f(-2000, -2000, -2000), ofVec3f(2000, 2000, 2000))
	);
	gui.add(
		light2Pos.setup("light 2 pos", ofVec3f(200, 0, 200), ofVec3f(-2000, -2000, -2000), ofVec3f(2000, 2000, 2000))
	);
	gui.add(
		lightColor.setup("light color", ofColor(), ofColor(), ofColor(255, 255, 255))
	);
	gui.add(
		light2Color.setup("light 2 color", ofColor(), ofColor(), ofColor(255, 255, 255))
	);


	model.loadModel("monkemat.obj", true);
	model.setRotation(0, 180.0f, 0.0f, 0.0f, 1.0f);
	model.disableMaterials(); // do not draw model material
	
	cout << "mat spec = " << material.getSpecularColor() << endl;
	cout << "mat diff = " << material.getDiffuseColor() << endl;
	cout << "mat ambient = " << material.getAmbientColor() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
	light.setPosition(lightPos);
	light.setDiffuseColor(ofFloatColor(ofColor(lightColor)));

	light2.setPosition(light2Pos);
	light2.setDiffuseColor(ofFloatColor(ofColor(light2Color)));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	ofEnableLighting();
	cam.begin();
	light.enable();
	light2.enable();
	
	material.begin();
	model.drawFaces();
	material.end();

	light2.disable();
	light.disable();
	ofDisableLighting();
	
	// draw light with absolute color
	ofSetColor(light.getDiffuseColor());
	ofDrawSphere(lightPos, 20);
	ofDrawBitmapString("light", lightPos + ofVec3f(0, 40, 0));

	// draw light 2 with absolute color
	ofSetColor(light2.getDiffuseColor());
	ofDrawSphere(light2Pos, 20);
	ofDrawBitmapString("light 2", light2Pos + ofVec3f(0, 40, 0));

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
