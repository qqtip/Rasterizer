#include <iostream>
#include "Rasterizer.h"

using namespace std;

/** constructor */
/*
Rasterizer::Rasterizer(Image *img) :
   image(img),
   width(image->getWidth()),
   height(image->getHeight())
   */
Rasterizer::Rasterizer(int frameWidth, int frameHeight) :
   width(frameWidth),
   height(frameHeight)
{
   // initialize z buffer
   zBuf = (float**) malloc(width * sizeof(float*));
   pixelBuf = (float**) malloc(width * sizeof(float*));
   for (int i = 0; i < width; ++i) {
      zBuf[i] = (float*) malloc(height * sizeof(float));
      pixelBuf[i] = (float*) malloc(height * sizeof(float));
   }

   // set frustum bounds
   if (width > height) {// landscape
      frustum.right = (float)width/(float)height;
      frustum.top = 1;
   } else if (height > width) {// portrait
      frustum.right = 1;
      frustum.top = (float)height/(float)width;
   } else {// square
      frustum.right = frustum.top = 1;
   }
   frustum.left = -frustum.right;
   frustum.bottom = -frustum.top;

   cout << "l bound: " << frustum.left << ", r bound " << frustum.right << endl;
   cout << "t bound: " << frustum.top << ", b bound " << frustum.bottom << endl;
}

bool Rasterizer::rasterize(std::vector<float> posBuf, 
      std::vector<unsigned int> triBuf, unsigned char colormode) {
   int triCount = triBuf.size() / 3;
   triangles = (Triangle *)malloc(triCount * sizeof(Triangle));
   // check color mode
   if (colormode == 2) {
      // do stuff
   }

   for (int i = 0; i < triCount; ++i) {
      // create triangles
   }

   for (int i = 0; i < triCount; ++i) {
      //drawTriangle(triangles[i]);
   }

   return true;
}