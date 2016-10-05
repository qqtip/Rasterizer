#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

// number of vertices in a triangle
const int NUM_VERTICES = 3;
// number of values in a vertex (x, y, z, r, g, b)
const int NUM_VALUES = 6;

struct Vertex {
   Vertex(float x, float y, float z) :
      x(x), y(y), z(z)
   {
      r = 255;
      g = 105;
      b = 180;
   }
   float x;
   float y;
   float z;
   float r;
   float g;
   float b;
};

class Triangle
{
public:
   Triangle(Vertex v1, Vertex v2, Vertex v3);

   float getXMin() const { return xmin; }
   float getYMin() const { return ymin; }
   float getXMax() const { return xmax; }
   float getYMax() const { return ymax; }
   bool contains(float x, float y);
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
   float width;
   float height;
   // area of the triangle
   float area;

   void init();
};

#endif
