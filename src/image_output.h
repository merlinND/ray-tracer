#ifndef IMAGE_OUTPUT_H
#define IMAGE_OUTPUT_H

#include <vector>

#include "renderer/Color.h"

typedef std::vector<Color> Image;

void writeSampleImage(char const * path, uint width = 100, uint height = 100);
void writeImage(char const * path, uint width, uint height, Image buffer);

#endif
