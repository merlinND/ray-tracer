#include "AmbientLight.h"

AmbientLight::AmbientLight(float i, Color const & c)
  : Light(i, c) {

}

bool AmbientLight::intersects(Ray const & ray) {
  return true;
}
