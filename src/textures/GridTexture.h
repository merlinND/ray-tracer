#ifndef GRIDTEXTURE_H
#define GRIDTEXTURE_H

#include "ColorTexture.h"

/**
 * A texture with a grid pattern.
 */
class GridTexture : public ColorTexture {
public:
  GridTexture(Color const & primary = Colors::WHITE, Color const & secondary = Colors::DARK_GREY);

  virtual Color getColor(float s, float t) const;

protected:
  /**
   * Color of the grid lines
   */
  Color secondaryColor;
};

#endif
