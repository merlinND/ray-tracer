#ifndef IMAGE_OUTPUT_H
#define IMAGE_OUTPUT_H

#include "renderer/Image.h"

void writeSampleImage(char const * path, uint width = 100, uint height = 100);
void writeImage(Image const & image, char const * path);

#endif
