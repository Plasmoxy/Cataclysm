// XDDD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <GL\freeglut.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace sf;

// util
float randf() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float randfRange(float start, float end) {
	return start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (end - start)));
}

class RetardedSquare {
public:

	Vector2f a;
	Vector2f b;
	Vector3f color;

	float z = 0;

	RetardedSquare(Vector2f _a, Vector2f _b) {
		cout << "SQUARE CREATED" << endl;
		a = _a;
		b = _b;
	}

	// delegated constructor
	RetardedSquare(Vector2f _a, Vector2f _b, float _z) : RetardedSquare(_a, _b) {
		z = _z;
	}

	void render() {
		glColor3f(color.x, color.y, color.z);
		glBegin(GL_QUADS);
		glVertex3f(a.x, a.y, z);
		glVertex3f(b.x, a.y, z);
		glVertex3f(b.x, b.y, z);
		glVertex3f(a.x, b.y, z);
		glEnd();
	}
};

class App : RenderWindow {
public:

	// CORE

	App() : RenderWindow(VideoMode(800, 500, 32), "XDD Project - SFML OpenGL - Plasmoxy") {}

	Clock* mainClock;

	bool rotate = true;
	float angle = 0.f;

	float dt = 0.f;
	float t_stamp;

	// OBJECTS

	vector<RetardedSquare> squares;

	void start() {

		mainClock = &Clock();

		for (int i = 0; i < 5; i++) {
			float hsize = randfRange(5.f, 50.f);
			float sqx = randfRange(-100.f, 100.f);
			float sqy = randfRange(-100.f, 100.f);

			RetardedSquare temp(
				Vector2f(sqx-hsize, sqy-hsize),
				Vector2f(sqx+hsize, sqy+hsize),
				randfRange(-100.f, 100.f)
			);
			temp.color = Vector3f(randf(), randf(), randf());
			squares.push_back(temp);
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.f, 800/500.f, 1.f, 1000.0f); //fov, aspect, zNear, zFar

		t_stamp = mainClock->getElapsedTime().asSeconds();

		while (isOpen()) {
			update();
		}
	}

	void update() {
		float currentTime = mainClock->getElapsedTime().asSeconds();
		dt = currentTime - t_stamp;
		t_stamp = currentTime;

		// Process events
		for (Event e; pollEvent(e);) {
			if (e.type == Event::Closed)
				close();

			// Escape key : exit
			if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Escape))
				close();

			if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::A)) {
				rotate = !rotate;
			}
		}

		render();
		display();
	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		// reset matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// translate
		glTranslatef(0.f, 0.f, -200.f);

		if (rotate) {
			angle += 90*dt;
		}
		glRotatef(angle, 0.f, 1.f, 0.f);

		// -- RENDER --

		for (auto& sq : squares) {
			sq.render();
		}
		
	}
};

int main(int argc, char * argv) {

	srand(time(0));

	cout << "STARTING APP" << endl;
	
	App app;
	app.start();

	cout << "APP END" << endl;
	return EXIT_SUCCESS;
}