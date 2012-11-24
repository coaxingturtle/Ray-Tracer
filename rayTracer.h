#pragma once
#include "mainApp.h"
#include <math.h>

void phong(Vec normal, Vec toLight, Vec reflect, Vec toView, rgbf* inColor, rgbf* outColor);
void rayTrace(Vec point, Vec dir, int step, rgbf* color, double currRefrac);
Vec intersect(Vec point, Vec dir, int &index, char &type);
double raySphereIntersect(Vec point, Vec dir, double rad, Vec circlePos);
Vec findNormal(Vec point, int index, char type);
Vec findVecLight(Vec q);
Vec findReflect(Vec q, Vec normal);
double rayPlaneIntersect(Vec ori, Vec dir, Vec planeNorm, Vec planePoint);
Vec calcRefractionDir(Vec dir, Vec norm, double trans);