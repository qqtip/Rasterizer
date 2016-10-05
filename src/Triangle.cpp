#include <iostream>
#include <cmath>
#include "Triangle.h"

using namespace std;

const float EPSILON = 0.001;

/** Constructor */
Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) :
   vertices{ v1, v2, v3 }
{
   init();
}

/** Scales the triangle by the given amount and returns a pointer to it */
void Triangle::scale(float scale, float xSkew, float ySkew) {
   for (int i = 0; i < VERTEX_COUNT; ++i) {
      vertices[i].x = vertices[i].x * scale + xSkew;
      vertices[i].y = vertices[i].y * scale + ySkew;
   }
   init();
}

/** Determines whether the triangle contains the given x, y coordinates */
bool Triangle::contains(float x, float y) {

   //float beta = triangle.calcBetaFor(x, y);
   float beta = (((vertices[0].x - vertices[2].x) * (y - vertices[2].y) - 
      (x - vertices[2].x) * (vertices[0].y - vertices[2].y)) / 2) / area;
   //float gamma = triangle.calcGammaFor(x, y);
   float gamma = (((vertices[1].x - vertices[0].x) * (y - vertices[0].y) - 
      (x - vertices[0].x) * (vertices[1].y - vertices[0].y)) / 2) / area;
   float alpha = 1 - beta - gamma;
      
   return alpha > -EPSILON && beta > -EPSILON && gamma > -EPSILON;
}

/**
 * Calculates the barycentric beta value of the given pofloat in relation
 * to the triangle.
 */
float Triangle::calcBetaFor(float x, float y) {
   // (xa − xc)(y − yc) - (x − xc)(ya − yc)
   return (((vertices[0].x - vertices[2].x) * (y - vertices[2].y) - 
      (x - vertices[2].x) * (vertices[0].y - vertices[2].y)) / 2) / area;
}

/**
 * Calculates the barycentric gamma value of the given pofloat in relation
 * to the triangle.
 */
float Triangle::calcGammaFor(float x, float y) {
   // (xb − xa)(y − ya) - (x − xa)(yb − ya)
   return (((vertices[1].x - vertices[0].x) * (y - vertices[0].y) - 
      (x - vertices[0].x) * (vertices[1].y - vertices[0].y)) / 2) / area;
}

/** Calculates the red value of the pofloat with the given a, b, g values. */
unsigned char Triangle::calcRedFor(float alpha, float beta, float gamma) {
   return alpha * vertices[0].r + 
           beta * vertices[1].r + 
          gamma * vertices[2].r;
}

/** Calculates the green value of the pofloat with the given a, b, g values. */
unsigned char Triangle::calcGreenFor(float alpha, float beta, float gamma) {
   return alpha * vertices[0].g + 
           beta * vertices[1].g + 
          gamma * vertices[2].g;
}

/** Calculates the blue value of the pofloat with the given a, b, g values. */
unsigned char Triangle::calcBlueFor(float alpha, float beta, float gamma) {
   return alpha * vertices[0].b + 
           beta * vertices[1].b + 
          gamma * vertices[2].b;
}

/** Initializes the Triangle based on vertex values */
void Triangle::init() {
   xmin = INFINITY;
   ymin = INFINITY;
   xmax = -INFINITY;
   ymax = -INFINITY;

   // determine actual min/max values
   for (int i = 0; i < VERTEX_COUNT; ++i) {
      xmin = vertices[i].x < xmin ? vertices[i].x : xmin;
      xmax = vertices[i].x > xmax ? vertices[i].x : xmax;
      ymin = vertices[i].y < ymin ? vertices[i].y : ymin;
      ymax = vertices[i].y > ymax ? vertices[i].y : ymax;
   }
   
   // calculate height/width of bounding box
   width = xmax - xmin;
   height = ymax - ymin;

   // calculate area
   area = ((vertices[1].x - vertices[0].x) * 
           (vertices[2].y - vertices[0].y) - 
           (vertices[2].x - vertices[0].x) * 
           (vertices[1].y - vertices[0].y)) / 2;
}