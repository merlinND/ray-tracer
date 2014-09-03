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

  Image(uint w = DEFAULT_WIDTH);
  Image(uint w, uint h);
  ~Image();

  /**
   * Convenience method to instanciate an image (made of colors)
   * @param buffer An array of consecutive uint8_t read from a file
   * @param w Width (in pixels)
   * @param h Height (in pixels)
   *
   * @note We assume 3 color channels
   * @warning The returned image must be freed after use
   */
  static Image * fromArray(uint8_t const * buffer, uint w, uint h);
  /**
   * Convenience method to convert an image (made of colors)
   * to a buffer of consecutive uint8_t to be written as a file
   */
  Buffer toBuffer() const;

  Color get(uint x, uint y) const;
  std::vector<Color *> getNeighbors(uint x, uint y) const;
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
