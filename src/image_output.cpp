#include <iostream>
#include <jpeglib.h>

using namespace std;

#include "image_output.h"

typedef vector<uint8_t> Buffer;
uint const N_CHANNELS = 3;
uint const BITDEPTH = 8 * N_CHANNELS;

/**
 * Convenience method to convert an image (made of colors)
 * to a buffer of consecutive ints to be written as a file
 */
Buffer imageToBuffer(Image & image) {
  Buffer b;
  for(int i = 0; i < image.size(); ++i) {
    Pixel p = colorToPixel(image[i]);
    b.push_back(p[0]);
    b.push_back(p[1]);
    b.push_back(p[2]);
  }
  return b;
}

/**
 * Generate a random image and save it to `path` as JPG
 * @param path Path to output JPG image to
 */
void writeSampleImage(char const * path, uint width, uint height) {
  // Generate a random image
  Image buffer;
  // Image data
  for(int i = 0; i < (width * height); ++i) {
    buffer.push_back(getRandomColor());
  }

  writeImage(path, width, height, buffer);
}

/**
 *
 * @param path Path to output jpg image to
 * @see http://www.andrewewhite.net/wordpress/2008/09/02/very-simple-jpeg-writer-in-c-c/
 */
void writeImage(char const * path, uint width, uint height, Image image) {
  // Open output file
  FILE* file = fopen(path, "wb");
  if (!file) {
    cout << "Error opening " << path << endl;
    return;
  }

  Buffer buffer = imageToBuffer(image);

  // Setup libjpeg objects
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, file);

  // Configure jpeg image
  cinfo.image_width = width;
  cinfo.image_height = height;
  cinfo.input_components = N_CHANNELS; // RGB channels
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_start_compress(&cinfo, (boolean)true);
  // Default quality is 100
  //jpeg_set_quality (&cinfo, 75, true);


  // Points to a row of the image
  JSAMPROW row_pointer;
  while (cinfo.next_scanline < cinfo.image_height) {
    // Point to the first byte of the next line
    row_pointer = (JSAMPROW) &buffer[cinfo.next_scanline * N_CHANNELS * width];
    jpeg_write_scanlines(&cinfo, &row_pointer, 1);
  }

  // Cleanup
  jpeg_finish_compress(&cinfo);
  fclose(file);
}
