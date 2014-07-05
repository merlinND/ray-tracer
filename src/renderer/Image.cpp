#include "Image.h"

Image::Image(uint w, float ratio)
  : width(w), aspectRatio(ratio) {
  this->height = (this->width / this->aspectRatio);
  init();
}

Image::Image(uint w, uint h)
  : width(w), height(h) {
  this->aspectRatio = (this->width / this->height);
  init();
}

void Image::init() {
  this->colors = new Color*[this->width];
  for(int x = 0; x < this->width; ++x) {
    this->colors[x] = new Color[this->height];
  }
}

Image::~Image() {
  for(int x = 0; x < this->width; ++x) {
    delete[] this->colors[x];
  }
  delete[] this->colors;
}

Buffer Image::toBuffer() const {
  Buffer b;
  for(int x = 0; x < this->width; ++x) {
    for(int y = 0; y < this->height; ++y) {
      Pixel p = colorToPixel(this->colors[x][y]);
      b.push_back(p[0]);
      b.push_back(p[1]);
      b.push_back(p[2]);
    }
  }
  return b;
}

Color Image::get(uint x, uint y) {
  return this->colors[x][y];
}
void Image::set(uint x, uint y, Color c) {
  this->colors[x][y] = c;
}
