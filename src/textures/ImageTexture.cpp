#include "../util/image_input.h"

#include "ImageTexture.h"

ImageTexture::ImageTexture(char const * path, Color const & c)
  : ColorTexture(c) {
  this->image = readImage(path);
}

ImageTexture::~ImageTexture() {
  delete this->image;
}

Color ImageTexture::getColor(float s, float t) const {
  // TODO: read from image
  return this->color;
}
