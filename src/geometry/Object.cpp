#include "Object.h"

float const Object::EPSILON = 0.0000000001f;
float const Object::PUSH_BACK = 0.00005f;

Color const Object::DEFAULT_COLOR = Color(1, 1, 1);
Material const & Object::DEFAULT_MATERIAL = Material::PLASTIC;

Object::Object(Point const & pos, Color const & c, Material const & m)
  : position(pos), color(c), material(&m) {

}

void Object::moveTo(Point const & pos) {
  this->position = pos;

  // TODO: update world matrix
}

void Object::rotate(float rx, float ry, float rz) {
  // TODO: update world matrix
}


Color Object::getColor() const {
  return this->material.color;
}
void Object::setColor(Color const & color) {
  this->color = color;
}

Material const & Object::getMaterial() const {
  return *(this->material);
}
void Object::setMaterial(Material const & material) {
  this->material = &material;
}
