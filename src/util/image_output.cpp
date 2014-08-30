#include <iostream>
#include <jpeglib.h>

using namespace std;

#include "image_output.h"

uint const N_CHANNELS = 3;

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
      image.set(x, y, getRandomColor());
    }
  }

  writeImage(image, path);
}

/**
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
  struct jpeg_compress_struct info;
  struct jpeg_error_mgr jerr;

  info.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&info);
  jpeg_stdio_dest(&info, file);

  // Configure jpeg image
  info.image_width = image.width;
  info.image_height = image.height;
  info.input_components = N_CHANNELS; // RGB channels
  info.in_color_space = JCS_RGB;
  jpeg_set_defaults(&info);
  jpeg_set_quality (&info, 100, (boolean)false);
  jpeg_start_compress(&info, (boolean)true);

  // Points to a row of the image
  JSAMPROW row_pointer;
  Buffer buffer = image.toBuffer();
  while (info.next_scanline < info.image_height) {
    // Point to the first byte of the next line
    row_pointer = (JSAMPROW) &buffer[info.next_scanline * N_CHANNELS * info.image_width];
    jpeg_write_scanlines(&info, &row_pointer, 1);
  }

  // Cleanup
  jpeg_finish_compress(&info);
  fclose(file);
}
