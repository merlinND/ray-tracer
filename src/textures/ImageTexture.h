#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "ColorTexture.h"

/**
 * A texture with based on an image.
 */
class ImageTexture : public ColorTexture {
public:
  ImageTexture(Color const & c = Colors::WHITE);

  // TODO: set image

  virtual Color getColor(float s, float t) const;

protected:
};

#endif
