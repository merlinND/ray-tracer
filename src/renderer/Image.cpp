#include <vector>
using namespace std;

#include "Camera.h"
#include "Image.h"

uint const Image::DEFAULT_WIDTH = 100;
uint const Image::DEFAULT_HEIGHT = 100;
float const Image::DEFAULT_ASPECT_RATIO = Camera::DEFAULT_ASPECT_RATIO;

Image::Image(uint w)
  : width(w), aspectRatio(DEFAULT_ASPECT_RATIO) {
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

Image * Image::fromBuffer(Buffer * buffer, uint w, uint h) {
  Image * result = new Image(w, h);

  // TODO
  for(uint y = 0; y < w; ++y) {
    for(uint x = 0; x < h; ++x) {
      result->set(x, y, Colors::GREY);
    }
  }

  return result;
}

Buffer Image::toBuffer() const {
  Buffer b;
  for(uint y = 0; y < this->height; ++y) {
    for(uint x = 0; x < this->width; ++x) {
      Pixel p = colorToPixel(this->colors[x][y]);
      b.push_back(p[0]);
      b.push_back(p[1]);
      b.push_back(p[2]);
    }
  }
  return b;
}

Color Image::get(uint x, uint y) const {
  return this->colors[x][y];
}
vector<Color *> Image::getNeighbors(uint x, uint y) const {
  vector<Color *> neighbors;

  if(x > 0)
    neighbors.push_back(&(this->colors[x-1][y]));
  if(y > 0)
    neighbors.push_back(&(this->colors[x][y-1]));
  if(x < this->width - 1)
    neighbors.push_back(&(this->colors[x+1][y]));
  if(y < this->height - 1)
    neighbors.push_back(&(this->colors[x][y+1]));

  return neighbors;
}
void Image::set(uint x, uint y, Color c) {
  this->colors[x][y] = c;
}
