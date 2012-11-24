#include "scene.h"

#include "mainApp.h"
#include "rayTracer.h"
#include <cstdlib>
#include <ctime>

/*
 this file is just a list of hard-coded scenes that could be rendered.
 */

void initObj0() {
	App->spheres[0].type = 's';
	App->spheres[0].pos.set(0.0, -4.0, -11.0);
	App->spheres[0].radius = 1.0;
	// {1, 0, 0} red
	App->spheres[0].color.r = 1.0; App->spheres[0].color.g = 0.0; App->spheres[0].color.b = 0.0;
	App->spheres[0].sigma = 0.0;
	
	App->spheres[1].type = 's';
	App->spheres[1].pos.set(-4.0, -4.0, -15.0);
	App->spheres[1].radius = 1.0;
	// {0, 0, 1} blue
	App->spheres[1].color.b = 1.0;
	//App->spheres[1].color.g = 1.0;
	App->spheres[1].sigma = 0.0;
	
	App->spheres[2].type = 's';
	App->spheres[2].pos.set(4.0, -4.0, -15.0);
	App->spheres[2].radius = 1.0;
	// {0, 1, 0} green
	App->spheres[2].color.g = 1.0;
	App->spheres[2].sigma = 0.0;
	
	App->spheres[3].type = 's';
	App->spheres[3].pos.set(0, -3, -17.0);
	App->spheres[3].radius = 2.0;
	// {1, 1, 1} white
	App->spheres[3].color.r = 1.0; App->spheres[3].color.g = 1.0; App->spheres[3].color.b = 1.0;
	App->spheres[3].sigma = 0.0;
	App->spheres[3].mirror = true;
	
	App->planes[0].lr.set(-10, -5, -10); //lower right corner
	App->planes[0].ur.set(-10, -5, -20); //upper right corner
	App->planes[0].ul.set(10, -5, -20); //upper left corner
	App->planes[0].ll.set(10, -5, -10); //lower left corner
	App->planes[0].type = 'p';
	App->planes[0].color.r = 0.5; App->planes[0].color.g = 0.5; App->planes[0].color.b = 0.5;
	App->planes[0].h = 30.0;
	App->planes[0].w = 30.0;
	//calc normal for plane
	Vec a = App->planes[0].ll - App->planes[0].lr;
	Vec b = App->planes[0].ur - App->planes[0].lr;
	App->planes[0].normal = cross(a, b);
	App->planes[0].sigma = 2;
	
	App->light.set(0, 10, -2);
	
}

void initObj1() {
	App->spheres[0].type = 's';
	App->spheres[0].pos.set(0.0, -4.0, -11.0);
	App->spheres[0].radius = 1.0;
	// {1, 1, 0} yellow
	App->spheres[0].color.r = 1.0; 
	App->spheres[0].color.g = 1.0;
	App->spheres[0].sigma = 2.0;
	
	App->spheres[1].type = 's';
	App->spheres[1].pos.set(-4.0, -2.0, -14.0);
	App->spheres[1].radius = 1.0;
	// {0, 1, 1} teal
	App->spheres[1].color.b = 1.0;
	App->spheres[1].color.g = 1.0;
	App->spheres[1].sigma = 2.0;
	
	App->spheres[2].type = 's';
	App->spheres[2].pos.set(4.0, 0.0, -12.0);
	App->spheres[2].radius = 1.0;
	// {0, 1, 0} green
	App->spheres[2].color.g = 1.0;
	App->spheres[2].sigma = 2.0;
	
	App->spheres[3].type = 's';
	App->spheres[3].pos.set(0, -2, -15.0);
	App->spheres[3].radius = 3.0;
	// {1, 1, 1} white
	App->spheres[3].color.r = 1.0; 
	App->spheres[3].color.g = 1.0; 
	App->spheres[3].color.b = 1.0;
	App->spheres[3].sigma = 2.0;
	
	App->planes[0].lr.set(-10, -5, -10); //lower right corner
	App->planes[0].ur.set(-10, -5, -20); //upper right corner
	App->planes[0].ul.set(10, -5, -20); //upper left corner
	App->planes[0].ll.set(10, -5, -10); //lower left corner
	App->planes[0].type = 'p';
	App->planes[0].color.r = 0.5; App->planes[0].color.g = 0.5; App->planes[0].color.b = 0.5;
	App->planes[0].h = 30.0;
	App->planes[0].w = 30.0;
	//calc normal for plane
	Vec a = App->planes[0].ll - App->planes[0].lr;
	Vec b = App->planes[0].ur - App->planes[0].lr;
	App->planes[0].normal = cross(a, b);
	App->planes[0].sigma = 0;
	
	App->light.set(15, 9, -6);
}

void initObj2() {
	App->spheres[0].type = 's';
	App->spheres[0].pos.set(0.0, -4.0, -11.0);
	App->spheres[0].radius = 1.0;
	// {1, 1, 0} yellow
	App->spheres[0].color.r = 1.0; 
	App->spheres[0].color.g = 1.0;
	App->spheres[0].sigma = 0.0;
	
	App->spheres[1].type = 's';
	App->spheres[1].pos.set(-4.0, -2.0, -14.0);
	App->spheres[1].radius = 1.0;
	// {0, 1, 1} teal
	App->spheres[1].color.b = 1.0;
	App->spheres[1].color.g = 1.0;
	App->spheres[1].sigma = 0.0;
	
	App->spheres[2].type = 's';
	App->spheres[2].pos.set(4.0, 0.0, -12.0);
	App->spheres[2].radius = 2.0;
	// {1, 0, 1} purple
	App->spheres[2].color.r = 1.0;
	App->spheres[2].color.b = 1.0;
	App->spheres[2].sigma = 0.0;
	
	App->spheres[3].type = 's';
	App->spheres[3].pos.set(0, -2, -15.0);
	App->spheres[3].radius = 3.0;
	// {1, 1, 1} white
	App->spheres[3].color.r = 1.0; 
	App->spheres[3].color.g = 1.0; 
	App->spheres[3].color.b = 1.0;
	App->spheres[3].sigma = 0.0;
	
	App->planes[0].lr.set(-10, -5, -10); //lower right corner
	App->planes[0].ur.set(-10, -5, -20); //upper right corner
	App->planes[0].ul.set(10, -5, -20); //upper left corner
	App->planes[0].ll.set(10, -5, -10); //lower left corner
	App->planes[0].type = 'p';
	App->planes[0].color.r = 0.5; App->planes[0].color.g = 0.5; App->planes[0].color.b = 0.5;
	App->planes[0].h = 30.0;
	App->planes[0].w = 30.0;
	//calc normal for plane
	Vec a = App->planes[0].ll - App->planes[0].lr;
	Vec b = App->planes[0].ur - App->planes[0].lr;
	App->planes[0].normal = cross(a, b);
	App->planes[0].sigma = 1;
	App->planes[0].mirror = true;
	
	App->light.set(-11, 10, 3);
}

void initObj3() {
	App->spheres[0].type = 's';
	App->spheres[0].pos.set(5.5, -4.0, -12.0);
	App->spheres[0].radius = 1.0;
	// {1, 1, 0} yellow
	App->spheres[0].color.r = 1.0; 
	App->spheres[0].color.g = 1.0;
	App->spheres[0].sigma = 2.0;
	
	App->spheres[1].type = 's';
	App->spheres[1].pos.set(3, -3.0, -14);
	App->spheres[1].radius = 2.0;
	// {0, 1, 1} teal
	App->spheres[1].color.b = 1.0;
	App->spheres[1].color.g = 1.0;
	App->spheres[1].sigma = 2.0;
	
	App->spheres[2].type = 's';
	App->spheres[2].pos.set(-1.0, -2.0, -18.0);
	App->spheres[2].radius = 3.0;
	// {1, 0, 1} purple
	App->spheres[2].color.r = 1.0;
	App->spheres[2].color.b = 1.0;
	App->spheres[2].sigma = 2.0;
	
	App->spheres[3].type = 's';
	App->spheres[3].pos.set(-8, -1, -25.0);
	App->spheres[3].radius = 4.0;
	// {2, 1, 0} red
	App->spheres[3].color.r = 2.0; 
	App->spheres[3].color.g = 1.0; 
	App->spheres[3].sigma = 2.0;
	//App->spheres[3].trans = 1.2; //glass
	
	App->planes[0].lr.set(-10, -5, -10); //lower right corner
	App->planes[0].ur.set(-10, -5, -20); //upper right corner
	App->planes[0].ul.set(10, -5, -20); //upper left corner
	App->planes[0].ll.set(10, -5, -10); //lower left corner
	App->planes[0].type = 'p';
	App->planes[0].color.r = 0.5; App->planes[0].color.g = 0.5; App->planes[0].color.b = 0.5;
	App->planes[0].h = 30.0;
	App->planes[0].w = 30.0;
	//calc normal for plane
	Vec a = App->planes[0].ll - App->planes[0].lr;
	Vec b = App->planes[0].ur - App->planes[0].lr;
	App->planes[0].normal = cross(a, b);
	App->planes[0].sigma = 0;
	
	App->light.set(8, 10, -2);
}

void initObj4() {
	srand(time(0));
	for (int i = 0; i < NUM_SPHERE; i++) {
		App->spheres[i].type = 's';
		int x = (rand() % 10); //random between 0 and 10
		int y = (rand() % 10); //random between 0 and 10
		int z = (rand() % 20) -30; //random between -30 and -10
		App->spheres[i].pos.set(x, y, z);
		float rad = ((float)rand()/(float)RAND_MAX) * 5.0; //random float between 0 and 5
		App->spheres[i].radius = rad;
		float sig = ((float)rand()/(float)RAND_MAX) * 5.0; //random float between 0 and 5
		App->spheres[i].sigma = sig;
		
		App->spheres[i].color.r = ((float)rand()/(float)RAND_MAX)*4; //0 to 4.0
		App->spheres[i].color.g = ((float)rand()/(float)RAND_MAX)*4; //0 to 4.0
		App->spheres[i].color.b = ((float)rand()/(float)RAND_MAX)*4; //0 to 4.0
	}
}

void initObj5() {
	App->spheres[0].type = 's';
	App->spheres[0].pos.set(5.0, -4.0, -10.0);
	App->spheres[0].radius = 1.0;
	App->spheres[0].color.r = 1.0; 
	App->spheres[0].sigma = 2.0;
	
	App->spheres[1].type = 's';
	App->spheres[1].pos.set(3.0, -30.0, -50);
	App->spheres[1].radius = 10.0;
	App->spheres[1].color.b = 2.0;
	App->spheres[1].color.r = 1.0;
	App->spheres[1].sigma = 2.0;
	
	App->spheres[2].type = 's';
	App->spheres[2].pos.set(0.0, -2.0, -30);
	App->spheres[2].radius = 5.0;
	// {1, 2, 0} purple
	App->spheres[2].color.r = 2.0;
	App->spheres[2].color.g = 1.0;
	App->spheres[2].sigma = 2.0;
	
	App->spheres[3].type = 's';
	App->spheres[3].pos.set(-30, -10, -30.0);
	App->spheres[3].radius = 20.0;
	// {0, 1, 2} blue-teal
	App->spheres[3].color.b = 1.0; 
	App->spheres[3].color.g = 2.0; 
	App->spheres[3].sigma = 2.0;
	
	App->light.set(27, 7, -23);
	
}