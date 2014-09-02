#ifndef COLORTEXTURE_H
#define COLORTEXTURE_H

#include "Texture.h"

/**
 * A texture with constant uniform color
 */
class ColorTexture : public Texture {
public:
  ColorTexture(Color const & c);

  virtual Color getColor(float s, float t) const;

protected:
  Color color;
};

#endif
