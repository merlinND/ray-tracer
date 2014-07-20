#include "Object.h"

float const Object::EPSILON = 0.000001f;

Color const Object::DEFAULT_COLOR = Color(1, 1, 1);
Material const & Object::DEFAULT_MATERIAL = Material::PLASTIC;

Object::Object(Point const & pos, Color const & c, Material const & m)
  : position(pos), color(c), material(m) {

}

Color Object::getColor() const {
  return this->color;
}

void Object::setColor(Color const & color) {
  this->color = color;
}
