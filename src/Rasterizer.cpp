#include <iostream>
#include <cmath>
#include "Rasterizer.h"
#include "Triangle.h"

using namespace std;

const float EPSILON = 0.001;

/** constructor */
Rasterizer::Rasterizer(int width, int height, Image *image) :
   width(width),
   height(height),
   image(image)
{
   // initialize z buffer
   zBuf = (float**) malloc(width * sizeof(float*));
   for (int i = 0; i < width; ++i) {
      zBuf[i] = (float*) malloc(height * sizeof(float));
      // initalize all values to negative infinity
      for (int j = 0; j < height; ++j)
         zBuf[i][j] = -INFINITY;
   }
}

bool Rasterizer::rasterize(std::vector<float> posBuf, 
      std::vector<unsigned int> triBuf, unsigned char colormode) {
   int count = triBuf.size() / 3;

   readTriangles(posBuf, triBuf);
   computeBoundingBox(count);

   for (int i = 0; i < count; ++i) {
      triangles[i].scale(scale, xSkew, ySkew);
      drawTriangle(triangles[i]);
   }

   return true;
}

/** Initializes Triangle collection from the provided mesh data */
void Rasterizer::readTriangles(std::vector<float> posBuf, 
      std::vector<unsigned int> triBuf) {
   int count = triBuf.size() / 3;
   // initialize triangle collection
   triangles = (Triangle *)malloc(count * sizeof(Triangle));

   // create Triangles objects for each triangle
   for (int i = 0; i < count; ++i) {
      // create a container for the vertices of the current triangle
      Vertex *vertices = (Vertex *)malloc(VERTEX_COUNT * sizeof(Vertex));
      // add each vertex of the current triangle
      for (int j = 0; j < VERTEX_COUNT; ++j) {
         int k = i * 3;
         // get the first index of the vertex from triangle buffer
         unsigned int vIndex = triBuf[k + j] * 3;

         float x = posBuf[vIndex];
         float y = posBuf[vIndex + 1]; 
         float z = posBuf[vIndex + 2];
         // create vertex and add to trio
         vertices[j] = Vertex(x, y, z);
      }
      // create and add the triangle
      Triangle tri(vertices[0], vertices[1], vertices[2]);
      triangles[i] = tri;

      free(vertices);
   }
}

/** Procedure computes the min/max x/y values covered by the shape */
void Rasterizer::computeBoundingBox(int count) { // inject count
   float left = INFINITY;
   float right = -INFINITY;
   float bottom = INFINITY;
   float top = -INFINITY;

   // compute bounding box by finding min/max x, y values
   for (int i = 0; i < count; ++i) {
      Triangle * current = &triangles[i];

      if (current->getXMin() < left)
         left = current->getXMin();
      if (current->getXMax() > right)
         right = current->getXMax();
      if (current->getYMin() < bottom)
         bottom = current->getYMin();
      if (current->getYMax() > top)
         top = current->getYMax();
   }

   // calculate scale to fit vertical
   if (height / (top - bottom) >= width / (right - left)) {
      scale = width / (right - left);
      xSkew = (right - left) * scale / 2;
      ySkew = height / 2;
   } else { // scale to fit horizontal
      scale = height / (top - bottom);
      xSkew = width / 2;
      ySkew = (top - bottom) * scale / 2;
   }
}

/** Draws the triangle onto the image */
void Rasterizer::drawTriangle(Triangle triangle) {
   float ymin = triangle.getYMin();
   float ymax = triangle.getYMax();
   float xmin = triangle.getXMin();
   float xmax = triangle.getXMax();

   // check all pixels in the bounding box
   for (int y = ymin; y < ymax; ++y) {
      for (int x = xmin; x < xmax; ++x) {
         // draw pixel if the current triangle contains it
         if (triangle.contains(x, y)) {
            
            unsigned char r = 255;//trip->calcRedFor(alpha, beta, gamma);
            unsigned char g = 105;//trip->calcGreenFor(alpha, beta, gamma);
            unsigned char b = 180;//trip->calcBlueFor(alpha, beta, gamma);
            image->setPixel(x, y, r, g, b);
         }
      }
   }
}