#include "Light.h"

Color const Light::DEFAULT_COLOR = Colors::WHITE;
// TODO: tweak value
float const Light::EPSILON = 0.001;

Light::Light(float i, Color const & c)
  : intensity(i), color(c) {

}

float Light::getParticipation(Scene const & scene, Ray const & lightRay) {
  return this->computeAttenuation(lightRay.from) * this->computeParticipation(scene, lightRay);
}

float Light::computeAttenuation(Point const & source) {
  return 1;
}

Color Light::getColor() const {
  return this->intensity * this->color;
}

void Light::setColor(Color const & c) {
  this->color = c;
}
