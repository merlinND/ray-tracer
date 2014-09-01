#include "GridTexture.h"

GridTexture::GridTexture(Color const & primary, Color const & secondary)
  : ColorTexture(primary), secondaryColor(secondary) {

}

Color GridTexture::getColor(float s, float t) const {
  // TODO: make customizable
  float size = 10;
  int thinness = 5;
  s *= size * thinness;
  t *= size * thinness;
  return (((int)s % (2 * thinness) == 0) || ((int)t % (2 * thinness) == 0)) ? this->secondaryColor : this->color;
}
