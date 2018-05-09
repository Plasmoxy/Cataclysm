#pragma once
#include "ofMain.h"

class Entity {
public:

	ofVec2f pos, vel, acc; // position, velocity, acceleration
	ofColor color;

	Entity(float x, float y);

	virtual void update(double dt);
	virtual void draw();
	void applyForce(ofVec2f force);

};

class Vehicle : public Entity {
public:

	ofVec2f desVel; // desired velocity
	ofVec2f steeringForce;

	Vehicle(float x, float y);

	virtual void update(float dt);

};