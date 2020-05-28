#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	ofxPanel gui;
	ofxVec3Slider lightPos;
	ofxVec3Slider light2Pos;
	ofxColorSlider lightColor;
	ofxColorSlider light2Color;
	ofxButton yeetBtn;

	ofEasyCam cam;

	ofxAssimpModelLoader model;
	ofMaterial material;
	ofTexture texture;
	ofLight light;
	ofLight light2;
	ofMesh mesh;

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
