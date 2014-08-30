#include <iostream>
#include <jpeglib.h>

using namespace std;

#include "image_input.h"

uint const N_CHANNELS = 3;
uint const BITDEPTH = 8 * N_CHANNELS;

/**
 * @param path Path to read a jpg image from
 * @see
 * @warning The image must be freed after use
 */
Image * readImage(char const * path) {
  // Open input file
  FILE* file = fopen(path, "r");
  if (!file) {
    cout << "Error opening " << path << endl;
    return NULL;
  }

  // TODO
  Image result;

  fclose(file);


  return &result;
}
