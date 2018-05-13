
//#include <Windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

const char* title = "Opengl";

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

float ang = 0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity(); // Reset the model-view matrix
	glTranslatef(0, 0, -50.f);

	ang += 0.1f;
	glRotatef(ang, 0.f, 1.f, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.f, 0, 0);
	glLineWidth(3.5f);
	glBegin(GL_POLYGON);
	glVertex3f(-10.f, -10.f, 0.f);
	glVertex3f(-10.f, 10.f, 2.f);
	glVertex3f(10.f, 10.f, 3.f);
	glVertex3f(10.f, -10.f, 10.f);
	glEnd();

	glTranslatef(0, 0, 5.f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.f, 1.f, 0);
	glLineWidth(2.5f);
	glBegin(GL_QUADS);
	glVertex3f(-10.f, -10.f, 0.f);
	glVertex3f(-10.f, 10.f, 2.f);
	glVertex3f(10.f, 10.f, 3.f);
	glVertex3f(10.f, -10.f, 10.f);
	glEnd();

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
	glutPostRedisplay();
}

// resize
void reshape(GLsizei width, GLsizei height) {

	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void keySpecial(int key, int x, int y) {

}

void keySpecialUp(int key, int x, int y) {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keySpecial);
	glutSpecialUpFunc(keySpecialUp);

	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}
