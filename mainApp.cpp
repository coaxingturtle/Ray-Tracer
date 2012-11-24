#include <stdlib.h>
#include <stdio.h>
#include "mainApp.h"
#include "rayTracer.h"
#include <math.h>
#include "draw.h"
#include "scene.h"
#include <iostream>

using namespace std;

AppState* App;

//==========================================================================
// appKeyboardFunc is called every time a "normal" ascii key is pressed
//==========================================================================
void appKeyboardFunc (unsigned char key, int x, int y) {
	switch (key) { 
		case 'r': App->rayTracing = !App->rayTracing; break;
		case ' ': printf("%f, %f, %f\n", App->light.x, App->light.y, App->light.z); break;
		case '8': App->light.y += 1; break;
		case '2': App->light.y -= 1; break;
		case '6': App->light.x += 1; break;
		case '4': App->light.x -= 1; break;
		case '9': App->light.z += 1; break;
		case '7': App->light.z -= 1; break;
		case '=': App->fovy += 5; break;
		case '-': App->fovy -= 5; break;
		case 27 : exit(1); // Esc was pressed
		default: return; // return without rendering
	}
	glutPostRedisplay();
}

//==========================================================================
// This appKeyboardFunc is for handling special keys. Note that this is 
// C++ and the parameter list differs from the other appKeyboardFunc
//==========================================================================
void appKeyboardFunc (int key, int x, int y) {
	const double incr=5;
	const double incf=0.5;
	switch (key) { 
		case GLUT_KEY_LEFT:      App->rotx+=incr; break;
		case GLUT_KEY_RIGHT:     App->rotx-=incr; break;
		case GLUT_KEY_UP:        App->roty-=incr; break;
		case GLUT_KEY_DOWN:      App->roty+=incr; break;
		case GLUT_KEY_PAGE_UP:   App->fovy-=incf; break;
		case GLUT_KEY_PAGE_DOWN: App->fovy+=incf; break;
		default: return; // return without rendering
	}
	// at this point the mark position changed and so we render the scene again:
	glutPostRedisplay();
}

//==========================================================================
// Called every time the window is resized
// Parameters w, h are the width and height of the window in pixels
//==========================================================================
void appResizeWindow (int w, int h) {
	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);	
 }

void appIdleFunc () {
}

//==========================================================================
// appDrawScene() will redraw the scene accodring to the current state of
// the application. For more complex scenes, display lists should be used.
//==========================================================================
void appDrawScene () {
	// Clear the rendering buffer:
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the viewing frustum for a coordinate range in [-10,10]^3
	int w = glutGet (GLUT_WINDOW_WIDTH);
	int h = glutGet (GLUT_WINDOW_HEIGHT);
	double aspect = double(w)/double(h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (App->fovy, aspect, 2/*znear*/, 50/*zfar*/);
	Vec ori = Vec(App->rotx/50.0, App->roty/50.0, 0);
	Vec focus = Vec(0, 0, -1);
	gluLookAt ( ori.x, ori.y, ori.z, // eye
	       focus.x, focus.y, focus.z,    // center
	       0, 1, 0 );  // up vector

	// Clear the model transformation stack:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_LIGHTING);
	GLfloat position[] = {App->light.x, App->light.y, App->light.z, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	// Drawing
	draw_scene();
	if (App->rayTracing) rtmain(h, w, ori, focus);
	
	// Show back buffer:
	glFlush();         // flush the pipeline (usually not necessary)
	glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

//==========================================================================
// This is the main. it will only run once.
//==========================================================================

int main (int argc, char** argv) {
	
	App = new AppState;
	App->spheres = new Sphere[NUM_SPHERE];
	App->rotx = 0;
	App->roty = 0;
	App->fovy = 60;
	App->rayTracing =  false;
	App->light.set(0, 10, -15);
	App->planes = new Plane[NUM_PLANES];
	cout << "Please input which scene to render(0-5): ";
	cin >> App->scene;
	
	switch (App->scene) {
		case 0: initObj0(); break;
		case 1: initObj1(); break;
		case 2: initObj2(); break;
		case 3: initObj3(); break;
		case 4: initObj4(); break;
		case 5: initObj5(); break;
		default: initObj0(); break;
	}

	// Init GLUT:
	glutInit (&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Window position (from top corner), and size (width and height)
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(360, 360);
	glutCreateWindow("Ray Tracer -- Justin Ray");

	// Display some info:
	printf ("GL_VENDOR : %s\n", (char*) glGetString (GL_VENDOR));
	printf ("GL_RENDERER : %s\n", (char*) glGetString (GL_RENDERER));
	printf ("GL_VERSION : %s\n", (char*) glGetString (GL_VERSION));

	// Initialize OpenGL settings as we want
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_POINT_SMOOTH);
	glEnable (GL_LINE_SMOOTH);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize (6);
	glLineWidth (1);
	
	//lighting/////////////////////
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat ambientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight[] = {  1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	
	// Set up GLUT callback functions for key presses
	glutKeyboardFunc (appKeyboardFunc);
	glutSpecialFunc (appKeyboardFunc);

	// Set up GLUT callback function for resizing windows
	glutReshapeFunc(appResizeWindow);

	// Set up GLUT callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	glutIdleFunc (appIdleFunc);

	// Print some info
	printf ("Press escape button to quit.\n");

	// Finally start the main loop

	// Note that glutMainLoop never returns so your program is entirely event-driven
	glutMainLoop ();
}
