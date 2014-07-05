#include "AmbientLight.h"

AmbientLight::AmbientLight(Color const & c)
  : Light(c) {

}

bool AmbientLight::intersects(Ray const & ray) {
  return true;
}
