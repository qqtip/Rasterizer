#include <iostream>
#include "Rasterizer.h"

using namespace std;

const float EPSILON = 0.001;

/** constructor */
Rasterizer::Rasterizer(int frameWidth, int frameHeight, Image *image) :
   width(frameWidth),
   height(frameHeight),
   image(image)
{
   // initialize z buffer
   zBuf = (float**) malloc(width * sizeof(float*));
   pixelBuf = (float**) malloc(width * sizeof(float*));
   for (int i = 0; i < width; ++i) {
      zBuf[i] = (float*) malloc(height * sizeof(float));
      pixelBuf[i] = (float*) malloc(height * sizeof(float));
   }
}

bool Rasterizer::rasterize(std::vector<float> posBuf, 
      std::vector<unsigned int> triBuf, unsigned char colormode) {
   int triCount = triBuf.size() / 3;
   triangles = (Triangle *)malloc(triCount * sizeof(Triangle));
   // check color mode
   if (colormode == 2) {
      // do stuff
   }

   for (unsigned int what : triBuf)
      cout << what << endl;

   for (int i = 0; i < triCount; ++i) {
      // create triangles
      int j = i * 3;
      unsigned int va = triBuf[j] * 3;
      unsigned int vb = triBuf[j + 1] * 3;
      unsigned int vc = triBuf[j + 2] * 3;

      Triangle tri(posBuf[va], posBuf[va + 1], posBuf[va + 2],
                   posBuf[vb], posBuf[vb + 1], posBuf[vb + 2],
                   posBuf[vc], posBuf[vc + 1], posBuf[vc + 2]);
      triangles[i] = tri;
   }

   for (int i = 0; i < triCount; ++i) {
      drawTriangle(triangles[i]);
   }

   return true;
}

void Rasterizer::drawTriangle(Triangle triangle) {
   float ymin = triangle.getYMin() * height / 2 + height/2;
   float ymax = triangle.getYMax() * height / 2 + height/2;
   float xmin = triangle.getXMin() * width / 2 + width/2;
   float xmax = triangle.getXMax() * width / 2 + width/2;

   for (int y = ymin; y < ymax; ++y) {
      for (int x = xmin; x < xmax; ++x) {
         // check if pixel is in bounds
         // split triangle into three triangles with point x,y
         //if (triangle.contains(x, y)) {
            unsigned char r = 255;//trip->calcRedFor(alpha, beta, gamma);
            unsigned char g = 105;//trip->calcGreenFor(alpha, beta, gamma);
            unsigned char b = 180;//trip->calcBlueFor(alpha, beta, gamma);
            image->setPixel(x, y, r, g, b);

         //}
      }
   }
}