#include "rayTracer.h"
#include <stdio.h>

//light defined to have no ambient, and white diffues and spec
#define I_D 1.0
#define I_S 1.0
#define SPEC 100.0
#define MAX_DEPTH 6

/**
 phong will fill out color with the result for the phong illumination equation.
 This will also check to see if in shaodw, and update accordingly
 */
void phong(Vec q, Vec normal, Vec toLight, Vec reflect, Vec toView, rgbf* inColor, rgbf* outColor) {
	
	int index = -1;
	char type = 'n';
	double shadowConst = 1.0;
	Vec newQ = q + (normal*0.00001); //to prevent self intersection
	Vec shadowFeeler = findVecLight(newQ);
	Vec temp = intersect(newQ, shadowFeeler, index, type);
	
	outColor->r = double(I_D)*(inColor->r/2)*(dot(toLight, normal))+double(I_S)*(inColor->r/2)*pow((dot(toView, reflect)),SPEC);
	outColor->g = double(I_D)*(inColor->g/2)*(dot(toLight, normal))+double(I_S)*(inColor->g/2)*pow((dot(toView, reflect)),SPEC);
	outColor->b = double(I_D)*(inColor->b/2)*(dot(toLight, normal))+double(I_S)*(inColor->b/2)*pow((dot(toView, reflect)),SPEC);
	
	if (index >= 0) { //in shadow
		shadowConst = 0.0;
		if (App->spheres[index].trans != 0) shadowConst = 0.8; //for refraction
		outColor->r *= shadowConst;
		outColor->g *= shadowConst;
		outColor->b *= shadowConst;
	}
}

/**
 This is the main ray tracer. works recursively. it has some frame work for refactions, though these dont work yet
 */
void rayTrace(Vec point, Vec dir, int step, rgbf* color, double currRefrac) {
	Vec q;
	color->r = 0.0;
	color->g = 0.0;
	color->b = 0.0;
	if (step > MAX_DEPTH) { //if at max, return background
		return;
	}
	int index = -1;
	char type = ' ';
	q = intersect(point, dir, index, type);
	if (index < 0) { //no point found
		return; //still background
	}
	
	Vec normal = findNormal(q, index, type);
	Vec toLight = findVecLight(q);
	Vec toView = point - q;
	toView.normalize();
	
	q = q + (normal*0.001); //to prevent self intersection
	Vec reflect = findReflect(q, normal);
	double sigma = 1.0;
	double trans = 0.0;
	if (type == 's') {
		phong(q, normal, toLight, reflect, toView, &App->spheres[index].color, color);
		sigma = App->spheres[index].sigma;
		trans = App->spheres[index].trans;
	}
	if (type == 'p') {
		phong(q, normal, toLight, reflect, toView, &App->planes[index].color, color);
		sigma = App->planes[index].sigma;
	}
	rgbf* reflected = new rgbf;
	rayTrace(q, reflect, step+1, reflected, 1.0);
	if ((App->spheres[index].mirror && type == 's') || (App->planes[index].mirror && type == 'p')) { //for mirrored objects
		color->r = reflected->r;
		color->g = reflected->r;
		color->b = reflected->r;
		sigma = 1.0;
	}
	if (trans != 0) {
		rgbf* transmitted = new rgbf;
		if (currRefrac == 1.0) { //if ray starts in air
			Vec transDir = calcRefractionDir(dir, normal, 1.0/trans); //going inside
			rayTrace(q, transDir, step+1, transmitted, trans);
		}
		else { 
			Vec transDir = calcRefractionDir(dir, normal, trans/1.0); //coming out
			rayTrace(q, transDir, step+1, transmitted, 1.0);
		}
		color->r += transmitted->r;
		color->g += transmitted->g;
		color->b += transmitted->b;
	}
	
	if (sigma == 0) return;
	color->r += reflected->r/sigma;
	color->g += reflected->g/sigma;
	color->b += reflected->b/sigma;
}

/**
 returns the nearest intersection point.
 Saves the index of the obj into the index pointer, if intersects nothing, index = -1
 */
Vec intersect(Vec point, Vec dir, int &index, char &type) {
	Vec q = Vec (-1, -1, -1);
	double t = 999999; //large number
	for (int i=0; i<NUM_SPHERE; i++) {
		double temp = raySphereIntersect(point, dir, App->spheres[i].radius, App->spheres[i].pos);
		if (temp < t) {
			t = temp;
			index = i;
			type = 's';
		}
	}
	//planes here
	for (int i = 0; i < NUM_PLANES; i++) {
		double temp = rayPlaneIntersect(point, dir, App->planes[i].normal, App->planes[i].ul);
		if (temp < t && temp > 0) {
			t = temp;
			index = i;
			type = 'p';
		}
	}
	q = point + (dir*t);
	return q;
}

/**
 used a sample math problem for an idea of how to do ray/sphere interations from wikipedia
 also used a psuedo code from "Real time rendering" 3rd ed.
 returns 't' of intersection
  */
double raySphereIntersect(Vec point, Vec dir, double rad, Vec circlePos) {
	double radSq = rad*rad;
	double t = 0.0;
	Vec loc = circlePos - point;
	double s = dot(loc, dir);
	double l = dot(loc, loc);
	if (s < 0 && l > radSq) return 9999999; //missed sphere
	double m = l - (s*s);
	if (m > radSq) return 9999999;
	double q = sqrt(radSq-(m));
	if (l > radSq) t = s - q;
	else t = s + q;
	return t;
}

double rayPlaneIntersect(Vec ori, Vec dir, Vec planeNorm, Vec planePoint) {
	double b = dot(planeNorm, dir);
	if (b == 0) return 9999999; //missed
	double t = (dot(planeNorm, (planePoint - ori)))/b;
	return t;
}

/**
 does not work yet. maybe.
 */
Vec calcRefractionDir(Vec dir, Vec norm, double trans) {
	double a = dot(norm, dir)*-1; //reverse direction
	double b = sqrt((1-(trans*trans))*(1-(a*a)));
	Vec result = (dir * trans) + (norm * (trans*a-b));
	result *= -1;
	return result;
}

/**
 returns the reflected ray given a point and normal. vector to light is calulated here
 */
Vec findReflect(Vec q, Vec normal) {
	Vec fromlight = q - App->light;
	fromlight.normalize();
	Vec temp = normal;
	temp *= (dot(fromlight, normal));
	temp *= 2.0;
	Vec r = fromlight - temp;
	return r;
}

Vec findVecLight(Vec q) {
	Vec vec = App->light - q;
	vec.normalize();
	return vec;
}

/**
 computes normal for a sphere and plane.
 if plane, normal is always the same
 */
Vec findNormal(Vec point, int index, char type) {
	Vec n;
	if (type == 's') {
		n = point - App->spheres[index].pos;
	}
	if (type == 'p') {
		n = App->planes[index].normal;
	}
	n.normalize();
	return n;
}