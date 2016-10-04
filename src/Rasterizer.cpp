#include <iostream>
#include "Rasterizer.h"

using namespace std;
// indices of RGB values in vertex array
const int R_VAL = 2;
const int G_VAL = 3;
const int B_VAL = 4;
/*
Triangle::Triangle(float x1, float y1, float z1, float r1, float g1, float b1, 
      float x2, float y2, float z2, float r2, float g2, float b2, 
      float x3, float y3, float z3, float r3, float g3, float b3) :
   vertices{ 
      { x1, y1, r1, g1, b1 }, 
      { x2, y2, r2, g2, b2 }, 
      { x3, y3, r3, g3, b3 }
   },*/
Triangle::Triangle(float x1, float y1, float z1,
      float x2, float y2, float z2,
      float x3, float y3, float z3) :
   vertices{ 
      { x1, y1, z1 }, 
      { x2, y2, z2 }, 
      { x3, y3, z3 }
   },
   // temporary min/max initializations
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
   height = ymax - ymin;
   width = xmax - xmin;

   // calculate area
   area = ((vertices[1][0] - vertices[0][0]) * 
           (vertices[2][1] - vertices[0][1]) - 
           (vertices[2][0] - vertices[0][0]) * 
           (vertices[1][1] - vertices[0][1])) / 2;
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