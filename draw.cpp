#include "mainApp.h"
#include <stdio.h>
#include "rayTracer.h"

/**
 draws a simple representaion of the scene using openGL rendering
 */
void draw_scene() {
	for (int i = 0; i < NUM_SPHERE; i++) {
		glColor3f(App->spheres[i].color.r,App->spheres[i].color.g,App->spheres[i].color.b);
		glPushMatrix();
			glTranslatef(App->spheres[i].pos.x, App->spheres[i].pos.y, App->spheres[i].pos.z);
			glutSolidSphere(App->spheres[i].radius, 50, 50);
		glPopMatrix();
	}
	
	for (int i = 0; i<NUM_PLANES; i++) {
		glColor3f(App->planes[i].color.r,App->planes[i].color.g,App->planes[i].color.b);
		glBegin(GL_QUADS);
		Vec lr = App->planes[0].lr;
		Vec ul = App->planes[0].ul;
		Vec ll = App->planes[0].ll;
		Vec ur = App->planes[0].ur;
		Vec norm = App->planes[0].normal;
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(lr.x, lr.y, lr.z);
		glVertex3f(ur.x, ur.y, ur.z);
		glVertex3f(ul.x, ul.y, ul.z);
		glVertex3f(ll.x, ll.y, ll.z);
		glEnd();
	}
	
}

/**
 Called by the main to start ray tracing. this sets the FOV for the rendering at 45 degrees
 Casts rays and prints the returned pixels to the screen
 */
void rtmain(int h, int w, Vec ori, Vec focus) {
	
	float fovX = 3.1415/4.5; //pi/4 or 45 degrees
	float fovY = (double(h)/double(w))*fovX; //based on aspect and fovX

	int size = w*h;
	int index = 0;
	float* pixels = new float[size*3];
	
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			float x = (((float(2)*(float)i)-(double)w)/(double)w)*tan(fovX);
			float y = (((float(2)*(float)j)-(double)h)/(double)h)*tan(fovY);
			Vec p = Vec(x, y, -1);
			Vec dir = p - ori;
			dir.normalize();
			rayTrace(p, dir, 0, (rgbf*)(&(pixels[(index++)*3])), 1.0);
		}
	}
	glDrawPixels(w, h, GL_RGB, GL_FLOAT, pixels);
}