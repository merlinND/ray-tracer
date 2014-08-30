#include <iostream>
#include <jpeglib.h>

using namespace std;

#include "image_input.h"

/**
 * @param path Path to read a jpg image from
 * @see
 * @warning The image must be freed after use
 */
Image * readImage(char const * path) {
  // Open input file
  FILE * file = fopen(path, "rb");
  if (!file) {
    cout << "Error opening " << path << endl;
    return NULL;
  }

  // Length of the file
  unsigned long data_size;
  uint width, height;
  // Number of color channels per pixel
  uint nChannels;
  // JPEG info data structure
  struct jpeg_decompress_struct info;
  jpeg_create_decompress(&info);
  // Error handler
  struct jpeg_error_mgr err;
  info.err = jpeg_std_error(&err);

  // Load info from the file
  jpeg_stdio_src(&info, file);
  jpeg_read_header(&info, (boolean)true);

  // Decompress the JPEG file
  jpeg_start_decompress(&info);

  width = info.output_width;
  height = info.output_height;
  nChannels = info.num_components;
  data_size = width * height * nChannels;

  // Our read buffer
  uint8_t * jdata = new uint8_t[data_size];
  // Points to an output row in `jdata`
  uint8_t * row_pointer;

  // Read scanlines one by one
  while(info.output_scanline < height) {
    // Point to the next output destination
    row_pointer = &jdata[info.output_scanline * nChannels * width];
    // Fill our `jdata` array with one more scanline from the image
    jpeg_read_scanlines(&info, &row_pointer, 1);
  }

  Image * result = Image::fromArray(jdata, width, height);

  // Cleanup
  jpeg_finish_decompress(&info);
  fclose(file);
  delete jdata;

  return result;
}
