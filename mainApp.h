#pragma once

#if defined WIN32
#include <glut/glut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h> 
#endif
#include "vec.h"

#define NUM_SPHERE 4
#define NUM_PLANES 1

struct rgbf {float r; float g; float b; bool background;};

struct Sphere {
	double radius, sigma, trans; // sigma = how reflective. inverted. trans is transmitence
	rgbf color;
	Vec pos;	
	char type; //type of object
	bool mirror;
};

struct Plane {
	double w, h, sigma; //sigma = how reflective. inverted
	rgbf color;
	Vec lr, ul, ll, ur, normal;
	char type;
	bool mirror;
};

struct AppState {
	double fovy, rotx, roty;
	Sphere* spheres;
	Plane* planes;
	bool rayTracing;
	Vec light;
	int scene;
};
extern AppState* App;

void appKeyboardFunc (unsigned char key, int x, int y);
void appKeyboardFunc (int key, int x, int y);
void appDrawScene ();
void appResizeWindow (int w, int h);
