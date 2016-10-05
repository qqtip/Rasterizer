#include <iostream>
#include "Rasterizer.h"

using namespace std;

const float EPSILON = 0.001;

/** constructor */
Rasterizer::Rasterizer(int width, int height, Image *image) :
   width(width),
   height(height),
   image(image),
   xScale(1),
   yScale(1)
{
   // initialize z buffer
   zBuf = (float**) malloc(width * sizeof(float*));
   pixelBuf = (float**) malloc(width * sizeof(float*));
   for (int i = 0; i < width; ++i) {
      zBuf[i] = (float*) malloc(height * sizeof(float));
      pixelBuf[i] = (float*) malloc(height * sizeof(float));
   }

   // determine x, y scales
   if (width > height)
      xScale =  width/height;
   else if (height > width)
      yScale = height/width;
   // if the image is square, maintain standard scale
}

bool Rasterizer::rasterize(std::vector<float> posBuf, 
      std::vector<unsigned int> triBuf, unsigned char colormode) {
   int triCount = triBuf.size() / 3;
   triangles = (Triangle *)malloc(triCount * sizeof(Triangle));
   // check color mode
   if (colormode == 2) {
      // do stuffR
   }

   // create triangles
   for (int i = 0; i < triCount; ++i) {
      // container of vertices that make up a triangle
      Vertex *vertices = (Vertex *)malloc(3 * sizeof(Vertex));
      // determine vertices for the current triangle
      for (int j = 0; j < 3; ++j) {
         int k = i * 3;
         // get the first index of the vertex from triangle buffer
         unsigned int vIndex = triBuf[k + j] * 3;
         // convert 3D coordinates to scaled 2D coordinates
         float x = posBuf[vIndex] * width / 2 * xScale + width / 2;
         float y = posBuf[vIndex + 1] * height / 2 * yScale + height / 2; 
         float z = posBuf[vIndex + 2];
         // create vertex and add to trio
         vertices[j] = Vertex(x, y, z);
      }
      // create and add the triangle
      Triangle tri(vertices[0], vertices[1], vertices[2]);
      triangles[i] = tri;
   }

   for (int i = 0; i < triCount; ++i)
      drawTriangle(triangles[i]);

   return true;
}

void Rasterizer::drawTriangle(Triangle triangle) {
   float ymin = triangle.getYMin();
   float ymax = triangle.getYMax();
   float xmin = triangle.getXMin();
   float xmax = triangle.getXMax();

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