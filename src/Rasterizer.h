#pragma once
#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Image.h"
#include "Triangle.h"

#define VERTEX_MAP( x ) ( ( (x) - 1 ) * 3 )

class Rasterizer
{
   public:
      Rasterizer(int width, int height, Image * image);
      bool rasterize(std::vector<float> posBuf, 
                     std::vector<unsigned int> triBuf,
                     unsigned char colormode);
      //Image getImage() const { return Raster; }

   private:
      float **zBuf;
      int width;
      int height;
      Image *image;
      Triangle *triangles;

      float scale;
      float xSkew;
      float ySkew;

      void readTriangles(std::vector<float> posBuf, 
                         std::vector<unsigned int> triBuf);
      void computeBoundingBox(int count);
      void drawTriangle(Triangle triangle);
};

#endif