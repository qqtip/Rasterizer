#include <iostream>
#include "Triangle.h"

using namespace std;
// indices of RGB values in vertex array
const int R_VAL = 2;
const int G_VAL = 3;
const int B_VAL = 4;

const float EPSILON = 0.001;

/** constructor */
Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) :
   vertices{ 
      { v1.x, v1.y, v1.z }, 
      { v2.x, v2.y, v2.z }, 
      { v3.x, v3.y, v3.z }
   },
   xmin(vertices[0][0]),
   ymin(vertices[0][1]),
   xmax(vertices[0][0]),
   ymax(vertices[0][1])
{
   // determine actual min/max values
   for (int i = 0; i < NUM_VERTICES; ++i) {
      xmin = vertices[i][0] < xmin ? vertices[i][0] : xmin;
      xmax = vertices[i][0] > xmax ? vertices[i][0] : xmax;
      ymin = vertices[i][1] < ymin ? vertices[i][1] : ymin;
      ymax = vertices[i][1] > ymax ? vertices[i][1] : ymax;
   }
   
   // calculate height/width of bounding box
   width = xmax - xmin;
   height = ymax - ymin;

   // calculate area
   area = ((vertices[1][0] - vertices[0][0]) * 
           (vertices[2][1] - vertices[0][1]) - 
           (vertices[2][0] - vertices[0][0]) * 
           (vertices[1][1] - vertices[0][1])) / 2;}

/** Determines whether the triangle contains the given x, y coordinates */
bool Triangle::contains(float x, float y) {

   //float beta = triangle.calcBetaFor(x, y);
   float beta = (((vertices[0][0] - vertices[2][0]) * (y - vertices[2][1]) - 
      (x - vertices[2][0]) * (vertices[0][1] - vertices[2][1])) / 2) / area;
   //float gamma = triangle.calcGammaFor(x, y);
   float gamma = (((vertices[1][0] - vertices[0][0]) * (y - vertices[0][1]) - 
      (x - vertices[0][0]) * (vertices[1][1] - vertices[0][1])) / 2) / area;
   float alpha = 1 - beta - gamma;
      
   return alpha > -EPSILON && beta > -EPSILON && gamma > -EPSILON;
}

/**
 * Calculates the barycentric beta value of the given pofloat in relation
 * to the triangle.
 */
float Triangle::calcBetaFor(float x, float y) {
   // (xa − xc)(y − yc) - (x − xc)(ya − yc)
   return (((vertices[0][0] - vertices[2][0]) * (y - vertices[2][1]) - 
      (x - vertices[2][0]) * (vertices[0][1] - vertices[2][1])) / 2) / area;
}

/**
 * Calculates the barycentric gamma value of the given pofloat in relation
 * to the triangle.
 */
float Triangle::calcGammaFor(float x, float y) {
   // (xb − xa)(y − ya) - (x − xa)(yb − ya)
   return (((vertices[1][0] - vertices[0][0]) * (y - vertices[0][1]) - 
      (x - vertices[0][0]) * (vertices[1][1] - vertices[0][1])) / 2) / area;
}

/** Calculates the red value of the pofloat with the given a, b, g values. */
unsigned char Triangle::calcRedFor(float alpha, float beta, float gamma) {
   return alpha * vertices[0][R_VAL] + 
           beta * vertices[1][R_VAL] + 
          gamma * vertices[2][R_VAL];
}

/** Calculates the green value of the pofloat with the given a, b, g values. */
unsigned char Triangle::calcGreenFor(float alpha, float beta, float gamma) {
   return alpha * vertices[0][G_VAL] + 
           beta * vertices[1][G_VAL] + 
          gamma * vertices[2][G_VAL];
}

/** Calculates the blue value of the pofloat with the given a, b, g values. */
unsigned char Triangle::calcBlueFor(float alpha, float beta, float gamma) {
   return alpha * vertices[0][B_VAL] + 
           beta * vertices[1][B_VAL] + 
          gamma * vertices[2][B_VAL];
}