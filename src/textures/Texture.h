#ifndef TEXTURE_H
#define TEXTURE_H

#include "../types.h"
#include "../renderer/Color.h"

class Texture {
public:
  // TODO: make textures scalable
  // TODO: allow textures to be rotated
  // TODO: image-based textures
  Texture();

  /**
   * @param s Horizontal coordinate (from 0 to 1)
   * @param t Vertical coordinate (from 0 to 1)
   */
  virtual Color getColor(float s, float t) const = 0;

protected:

};

#endif