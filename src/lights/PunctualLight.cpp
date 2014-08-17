#include "../scenes/Scene.h"
#include "PunctualLight.h"

PunctualLight::PunctualLight(Point const & p, float i, Color const & c)
  : Light(i, c), position(p) {

}

float PunctualLight::computeParticipation(Scene const & scene, Ray const & lightRay) {
  return (scene.isObstructed(lightRay, this->position) ? 0 : 1);
}

float PunctualLight::computeAttenuation(Point const & source) {
  float distance = (this->position - source).squaredNorm();
  // TODO
  return 1;
}
