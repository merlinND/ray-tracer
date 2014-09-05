#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "../renderer/Image.h"

#include "ColorTexture.h"

/**
 * A texture with based on an image.
 */
class ImageTexture : public ColorTexture {
public:
  Image * image;
  // TODO: support offset
  // TODO: support rotation (by PI/2 increments)

  ImageTexture(char const * path, Color const & c = Colors::WHITE);
  ~ImageTexture();

  virtual Color getColor(float s, float t) const;

protected:

  static Color const MISSING_TEXTURE_COLOR;
};

#endif
