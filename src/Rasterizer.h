#pragma once
#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Image.h"
#include "Triangle.h"

struct Vertex {
   float x;
   float y;
   float z;
   float r;
   float g;
   float b;
};

struct Frustum {
   float left;
   float right;
   float top;
   float bottom;
};

class Rasterizer
{
   public:
      //Rasterizer(Image *img);
      Rasterizer(int frameWidth, int frameHeight);
      bool rasterize(std::vector<float> posBuf, 
                     std::vector<unsigned int> triBuf,
                     unsigned char colormode);
      //Image getImage() const { return Raster; }

   private:
      //*Image pixelBuf;
      //Image *image;
      float **pixelBuf;
      float **zBuf;
      Frustum frustum;
      int width;
      int height;
      //int imgWidth;
      //int imgHeight;
      Triangle *triangles;

      void drawTriangle(Triangle triangle);
};

#endif