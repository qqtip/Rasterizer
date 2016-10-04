#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

// number of vertices in a triangle
const int NUM_VERTICES = 3;
// number of values in a vertex (x, y, r, g, b)
const int NUM_VALUES = 5;

class Triangle
{
public: /*
   Triangle(float x1, float y1, float z1, float r1, float g1, float b1, 
      float x2, float y2, float z2, float r2, float g2, float b2, 
      float x3, float y3, float z3, float r3, float g3, float b3);
      */

   Triangle(float x1, float y1, float z1,
      float x2, float y2, float z2,
      float x3, float y3, float z3);


   float getXMin() const { return xmin; }
   float getYMin() const { return ymin; }
   float getXMax() const { return xmax; }
   float getYMax() const { return ymax; }
   float calcBetaFor(float x, float y);
   float calcGammaFor(float x, float y);
   unsigned char calcRedFor(float alpha, float beta, float gamma);
   unsigned char calcGreenFor(float alpha, float beta, float gamma);
   unsigned char calcBlueFor(float alpha, float beta, float gamma);

private:
   // x, y, r, b, g values of each vertex
   float vertices[NUM_VERTICES][NUM_VALUES];
   // min/max coordinate values
   float xmin;
   float ymin;
   float xmax;
   float ymax;
   // height and width of bounding box
   float height;
   float width;
   // area of the triangle
   float area;
};

#endif
