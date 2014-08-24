#include "ColorTexture.h"

ColorTexture::ColorTexture(Color const & c)
  : color(c) {

}

Color ColorTexture::getColor(float s, float t) {
  return this->color;
}
