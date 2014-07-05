#include "Object.h"

Object::Object(Point const & pos, Material const & m)
  : position(pos), material(m) {

}

Color Object::getColor() const {
  return this->material.color;
}
