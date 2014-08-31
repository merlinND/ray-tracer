#include "ImageTexture.h"

ImageTexture::ImageTexture(Color const & c)
  : ColorTexture(c) {

}

Color ImageTexture::getColor(float s, float t) const {
  // TODO: read from image
  return this->color;
}
