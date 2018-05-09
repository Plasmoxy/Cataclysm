#include "objects.h"

// --- Entity ---

Entity::Entity(float x, float y) :
	pos(x, y),
	color(255)
{
	
}

void Entity::update(double dt) {
	vel += acc * dt;
	pos += vel * dt;
	acc *= 0;
}

void Entity::draw() {
	ofPushStyle();
	ofPushMatrix();

	ofSetColor(color);
	ofTranslate(pos);

	ofDrawRectangle(0, 0, 30, 30);
	

	ofPopMatrix();
	ofPopStyle();
}

void Entity::applyForce(ofVec2f force) {
	acc += force;
}


// --- Vehicle ---

Vehicle::Vehicle(float x, float y) :
	Entity(x, y)

{}

void Vehicle::update(float dt) {

	// Apply steering force
	// F_steer = v_desired - v_current

	steeringForce = desVel - vel;
	applyForce(steeringForce);

	Entity::update(dt);
}