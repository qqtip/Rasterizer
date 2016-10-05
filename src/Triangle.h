#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

// number of vertices in a triangle
const int VERTEX_COUNT = 3;

/* a vertex containing a location in 3D space and an RBG color value */
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

/* a triangle containing three vertices and functions to aid rasterization */
class Triangle
{
public:
   Triangle(Vertex v1, Vertex v2, Vertex v3);

   float getXMin() const { return xmin; }
   float getYMin() const { return ymin; }
   float getXMax() const { return xmax; }
   float getYMax() const { return ymax; }
   void scale(float scale, float xSkew, float ySkew);
   bool contains(float x, float y);
   float calcBetaFor(float x, float y);
   float calcGammaFor(float x, float y);
   unsigned char calcRedFor(float alpha, float beta, float gamma);
   unsigned char calcGreenFor(float alpha, float beta, float gamma);
   unsigned char calcBlueFor(float alpha, float beta, float gamma);

private:
   // x, y, r, b, g values of each vertex
   Vertex vertices[VERTEX_COUNT];
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
