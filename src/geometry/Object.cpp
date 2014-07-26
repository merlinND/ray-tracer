#include "Object.h"

float const Object::EPSILON = 0.0000000001f;
float const Object::PUSH_BACK = 0.000005f;

Object::Object(Point const & pos, Material const & m)
  : position(pos), material(m) {

}

Color Object::getColor() const {
  return this->material.color;
}


void Object::setColor(Color const & color) {
  this->material.color = color;
}
