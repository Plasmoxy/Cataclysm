#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
public:

	int mx, my;
	ofImage screenshot;
	int frame;

	ofxPanel gui;
	ofxIntSlider intSlider;
	ofxFloatSlider floatSlider;
	ofxButton button;
	ofxLabel label;
	ofxToggle toggle;
	ofxIntField intField;
	ofxFloatField floatField;
	ofxTextField textField;
	ofxVec2Slider vec2Slider;

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
};
