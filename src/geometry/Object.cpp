#include "Object.h"

float const Object::EPSILON = 0.000001f;

Object::Object(Point const & pos, Material const & m)
  : position(pos), material(m) {

}
