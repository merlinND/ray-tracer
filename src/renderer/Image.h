#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

#include "Color.h"

typedef std::vector<uint8_t> Buffer;

class Image
{
public:
  /** Image dimensions (in number of points) */
  uint width, height;
  float aspectRatio;

  // Default values
  static uint const DEFAULT_WIDTH;
  static uint const DEFAULT_HEIGHT;
  static float const DEFAULT_ASPECT_RATIO;

  Image(uint w = DEFAULT_WIDTH,
        float ratio = DEFAULT_ASPECT_RATIO);
  Image(uint w, uint h);
  ~Image();

  /**
   * Convenience method to convert an image (made of colors)
   * to a buffer of consecutive ints to be written as a file
   */
  Buffer toBuffer() const;

  Color get(uint x, uint y);
  void set(uint x, uint y, Color c);

protected:
  /** All the color points of this image, line after line */
  Color ** colors;

  /**
   * Initialize color matrix
   */
  void init();
};

#endif
