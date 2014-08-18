#include "../scenes/Scene.h"
#include "AmbientLight.h"

AmbientLight::AmbientLight(float i, Color const & c)
  : Light(i, c) {

}

float AmbientLight::computeParticipation(Scene const & scene, Ray const & lightRay) {
  return 1;
}
