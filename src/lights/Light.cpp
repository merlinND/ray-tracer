#include "Light.h"

Color const Light::DEFAULT_COLOR = Color(1, 1, 1);
// TODO: tweak value
float const Light::EPSILON = 0.001;

Light::Light(float i, Color const & c)
  : intensity(i), color(c) {

}

Color Light::getColor() const {
  return this->intensity * this->color;
}

void Light::setColor(Color const & c) {
  this->color = c;
}
