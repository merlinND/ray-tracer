#include <math.h>

#include "../scenes/Scene.h"
#include "PunctualLight.h"

PunctualLight::PunctualLight(Point const & p, float i, Color const & c)
  : Light(i, c), position(p) {

}

float PunctualLight::computeParticipation(Scene const & scene, Ray const & lightRay) {
  return (scene.isObstructed(lightRay, this->position) ? 0 : 1);
}

float PunctualLight::computeAttenuation(Point const & source) {
  if(this->position == source) {
    return 1;
  }

  float d2 = (this->position - source).squaredNorm();
  float d = std::sqrt(d2);
  float amount = 1 / (0.1 + 0.035 * d + 0.00001 * d2);

  return std::min(amount, 1.f);
}
