#pragma once

#include "ofMain.h"
#include "objects.h"

class ofApp : public ofBaseApp {
public:

	ofColor bgColor, rectColor;
	ofVec2f mouse;

	ofVec2f gravity;
	Vehicle v1;
	Entity e1;

	//std::vector<Entity> entities;

	double rectColorTimer;
	bool gravityOn;

	ofApp();

	void updateMouse();
	void updateRectColorTimer(double dt);
	ofColor getRandomColor();

	// ------

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
