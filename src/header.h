#ifndef _HEADER_H_
#define _HEADER_H_

void resize_obj(std::vector<tinyobj::shape_t> &shapes);
/* verifies correct command line usage and extracts them */
bool extractArguments(int argc, char **argv, std::string *meshName, 
      std::string *imgName, int *width, int *height, unsigned char *colormode);
/* Maps triangle and position buffer values onto indices */
#define VERTEX_MAP( x ) ( ( (x) - 1 ) * 3 )


#endif