#ifndef TEXTURE_H
#define TEXTURE_H

#include "../types.h"
#include "../renderer/Color.h"

class Texture {
public:
  Texture();

  /**
   * @param s Horizontal coordinate (from 0 to 1)
   * @param t Vertical coordinate (from 0 to 1)
   */
  virtual Color getColor(float s, float t) = 0;

protected:

};

#endif
