#include "PunctualLight.h"

PunctualLight::PunctualLight(Point const & p, float i, Color const & c)
  : Light(i, c), position(p) {

}

bool PunctualLight::intersects(Ray const & ray) {
  // TODO
  return true;
}
