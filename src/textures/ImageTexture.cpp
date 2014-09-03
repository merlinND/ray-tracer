#include "../util/image_input.h"

#include "ImageTexture.h"

Color const ImageTexture::MISSING_TEXTURE_COLOR = Colors::PURPLE;

ImageTexture::ImageTexture(char const * path, Color const & c)
  : ColorTexture(c) {
  this->image = readImage(path);
}

ImageTexture::~ImageTexture() {
  delete this->image;
}

Color ImageTexture::getColor(float s, float t) const {
  // Constant color as a "missing texture" warning
  if(this->image == NULL) {
    return ImageTexture::MISSING_TEXTURE_COLOR;
  }

  int x = std::floor(s * this->image->width);
  int y = std::floor(t * this->image->height);
  return this->image->get(x, y);
}
