/* Release code for program 1 CPE 471 Fall 2016 */

#include <iostream>
#include <string>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Image.h"
#include "Rasterizer.h"
#include "Triangle.h"
#include "header.h"

using namespace std;

const int MIN_ARGS = 5 + 1;
const float EPSILON = 0.001;

int main(int argc, char **argv)
{
   string meshName, imgName;
   int width, height;
   unsigned char colormode;

   // get arguments, print error and return if invalid arguments provided
   if (!extractArguments(argc, argv, 
         &meshName, &imgName, &width, &height, &colormode)) {
      cerr << "Usage: P01 meshfile imagefile width height colormode" << endl;
      exit(1);
   }

	// triangle buffer
	vector<unsigned int> triBuf;
	// position buffer
	vector<float> posBuf;
   // geometry
	vector<tinyobj::shape_t> shapes; 
   // material (unused)
	vector<tinyobj::material_t> objMaterials; 
	string errStr;
	
   bool rc = tinyobj::LoadObj(shapes, objMaterials, errStr, meshName.c_str());
	/* error checking on read */
	if(!rc) {
		cerr << errStr << endl;
      exit(2);
	}
 	// resize object to be within -1 -> 1
   resize_obj(shapes);
   posBuf = shapes[0].mesh.positions;
   triBuf = shapes[0].mesh.indices;

   /*
   //cout << "Number of vertices: " << posBuf.size()/3 << endl;
   //cout << "Number of triangles: " << triBuf.size()/3 << endl;
   for (float f : posBuf) {
      printf("%.2f ", f);
   }
   cout << endl;
   for (int i : triBuf) {
      printf("%d ", i);
   }
   cout << endl;
   //*/

   //create an image
   auto image = make_shared<Image>(width, height);
   // rasterize
   //Rasterizer rasterizer((Image*)((shared_ptr<Image>)image).get());
   Rasterizer rasterizer(width, height);
   rasterizer.rasterize(posBuf, triBuf, colormode);
   // write out the image
   image->writeToFile(imgName);

	return 0;
}

/*
   Helper function you will want all quarter
   Given a vector of shapes which has already been read from an obj file
   resize all vertices to the range [-1, 1]
 */
void resize_obj(std::vector<tinyobj::shape_t> &shapes) {
   float minX, minY, minZ;
   float maxX, maxY, maxZ;
   float scaleX, scaleY, scaleZ;
   float shiftX, shiftY, shiftZ;

   minX = minY = minZ = 1.1754E+38F;
   maxX = maxY = maxZ = -1.1754E+38F;

   //Go through all vertices to determine min and max of each dimension
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         if(shapes[i].mesh.positions[3*v+0] < minX) minX = shapes[i].mesh.positions[3*v+0];
         if(shapes[i].mesh.positions[3*v+0] > maxX) maxX = shapes[i].mesh.positions[3*v+0];

         if(shapes[i].mesh.positions[3*v+1] < minY) minY = shapes[i].mesh.positions[3*v+1];
         if(shapes[i].mesh.positions[3*v+1] > maxY) maxY = shapes[i].mesh.positions[3*v+1];

         if(shapes[i].mesh.positions[3*v+2] < minZ) minZ = shapes[i].mesh.positions[3*v+2];
         if(shapes[i].mesh.positions[3*v+2] > maxZ) maxZ = shapes[i].mesh.positions[3*v+2];
      }
   }

   //From min and max compute necessary scale and shift for each dimension
   float maxExtent, xExtent, yExtent, zExtent;
   xExtent = maxX - minX;
   yExtent = maxY - minY;
   zExtent = maxZ - minZ;
   if (xExtent >= yExtent && xExtent >= zExtent) {
      maxExtent = xExtent;
   }
   if (yExtent >= xExtent && yExtent >= zExtent) {
      maxExtent = yExtent;
   }
   if (zExtent >= xExtent && zExtent >= yExtent) {
      maxExtent = zExtent;
   }
   scaleX = 2.0 / maxExtent;
   shiftX = minX + (xExtent / 2.0);
   scaleY = 2.0 / maxExtent;
   shiftY = minY + (yExtent / 2.0);
   scaleZ = 2.0 / maxExtent;
   shiftZ = minZ + (zExtent / 2.0);

   //Go through all verticies shift and scale them
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         shapes[i].mesh.positions[3*v+0] = (shapes[i].mesh.positions[3*v+0] - shiftX) * scaleX;
         assert(shapes[i].mesh.positions[3*v+0] >= -1.0 - EPSILON);
         assert(shapes[i].mesh.positions[3*v+0] <= 1.0 + EPSILON);
         shapes[i].mesh.positions[3*v+1] = (shapes[i].mesh.positions[3*v+1] - shiftY) * scaleY;
         assert(shapes[i].mesh.positions[3*v+1] >= -1.0 - EPSILON);
         assert(shapes[i].mesh.positions[3*v+1] <= 1.0 + EPSILON);
         shapes[i].mesh.positions[3*v+2] = (shapes[i].mesh.positions[3*v+2] - shiftZ) * scaleZ;
         assert(shapes[i].mesh.positions[3*v+2] >= -1.0 - EPSILON);
         assert(shapes[i].mesh.positions[3*v+2] <= 1.0 + EPSILON);
      }
   }
}

bool extractArguments(int argc, char **argv, string *meshName, string *imgName, int *width, int *height, unsigned char *colormode) {
   // check total number of arguments
   if (argc < MIN_ARGS)
      return false;

   // initialize values
   *meshName = argv[1];
   *imgName = argv[2];
   *width = atoi(argv[3]);
   *height = atoi(argv[4]);
   *colormode = atoi(argv[5]);

   // check width and height
   if (*width < 1 || *height < 1) {
      cerr << "Width and height must be non-zero integers." << endl;
      return false;
   }

   // check color mode
   if (*colormode < 1 || *colormode > 2) {
      cerr << "Acceptable color mode values are 1 and 2." << endl;
      return false;
   }

   return true;
}

