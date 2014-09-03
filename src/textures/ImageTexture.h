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

  ImageTexture(char const * path, Color const & c = Colors::WHITE);
  ~ImageTexture();

  virtual Color getColor(float s, float t) const;

protected:
};

#endif
