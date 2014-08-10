#include "PunctualLight.h"

PunctualLight::PunctualLight(Point const & p, float i, Color const & c)
  : Light(i, c), position(p) {

}

float PunctualLight::getParticipation(Scene const & scene, Ray const & lightRay) {
  return (scene.isObstructed(lightRay, this->position) ? 0 : 1);
}
