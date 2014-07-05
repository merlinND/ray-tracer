#include <iostream>
#include <jpeglib.h>

using namespace std;

#include "image_output.h"

uint const N_CHANNELS = 3;
uint const BITDEPTH = 8 * N_CHANNELS;

/**
 * Generate a random image and save it to `path` as JPG
 * @param path Path to output JPG image to
 */
void writeSampleImage(char const * path, uint width, uint height) {
  // Generate a random image
  Image image(width, height);
  // Image data
  for(int x = 0; x < width; ++x) {
    for(int y = 0; y < height; ++y) {
      image.set(x, y, Color(0, 1, 1)); // getRandomColor()
    }
  }

  writeImage(image, path);
}

/**
 *
 * @param path Path to output jpg image to
 * @see http://www.andrewewhite.net/wordpress/2008/09/02/very-simple-jpeg-writer-in-c-c/
 */
void writeImage(Image const & image, char const * path) {
  // Open output file
  FILE* file = fopen(path, "wb");
  if (!file) {
    cout << "Error opening " << path << endl;
    return;
  }


  // Setup libjpeg objects
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, file);

  // Configure jpeg image
  cinfo.image_width = image.width;
  cinfo.image_height = image.height;
  cinfo.input_components = N_CHANNELS; // RGB channels
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_start_compress(&cinfo, (boolean)true);
  // Default quality is 100
  //jpeg_set_quality (&cinfo, 75, true);

  // Points to a row of the image
  JSAMPROW row_pointer;
  Buffer buffer = image.toBuffer();
  while (cinfo.next_scanline < cinfo.image_height) {
    // Point to the first byte of the next line
    row_pointer = (JSAMPROW) &buffer[cinfo.next_scanline * N_CHANNELS * cinfo.image_width];
    jpeg_write_scanlines(&cinfo, &row_pointer, 1);
  }

  // Cleanup
  jpeg_finish_compress(&cinfo);
  fclose(file);
}
