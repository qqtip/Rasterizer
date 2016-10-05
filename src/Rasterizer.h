#pragma once
#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Image.h"
#include "Triangle.h"

#define VERTEX_MAP( x ) ( ( (x) - 1 ) * 3 )

struct Vertex {
   float x;
   float y;
   float z;
   float r;
   float g;
   float b;
};

class Rasterizer
{
   public:
      Rasterizer(int frameWidth, int frameHeight, Image *image);
      bool rasterize(std::vector<float> posBuf, 
                     std::vector<unsigned int> triBuf,
                     unsigned char colormode);
      //Image getImage() const { return Raster; }

   private:
      float **pixelBuf;
      float **zBuf;
      int width;
      int height;
      Image *image;
      Triangle *triangles;

      void drawTriangle(Triangle triangle);
};

#endif