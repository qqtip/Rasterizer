#pragma once
#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Image.h"

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
      Rasterizer(Image img);
      bool rasterize(std::vector<float> *posBuf, 
                     std::vector<unsigned int> *triBuf);
      bool rasterize(std::vector<float> *posBuf, 
                     std::vector<unsigned int> *triBuf, int colormode = 1);
      //Image getImage() const { return Raster; }

   private:
      *std::vector<float> positions;
      *std::vector<unsigned int> indices;
      *Image pixelBuf;
      **float zBuf;
      void drawTriangle(Triangle triangle);
};

#endif