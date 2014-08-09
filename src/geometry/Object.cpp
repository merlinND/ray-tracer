#include <Eigen/Geometry>
#include "Object.h"

float const Object::EPSILON = 0.0000000001f;
float const Object::PUSH_BACK = 0.00005f;

Color const Object::DEFAULT_COLOR = Color(1, 1, 1);
Material const & Object::DEFAULT_MATERIAL = Material::PLASTIC;

Object::Object(Point const & pos, Color const & c, Material const & m)
  : color(c), material(&m) {

  this->worldMatrix = Eigen::Matrix3f::Identity();
  moveTo(pos);
}

void Object::moveTo(Point const & pos) {
  this->position = pos;
}

void Object::rotate(float rx, float ry, float rz) {
  // TODO: update world matrix
}

bool Object::intersects(Ray const & ray, Intersection * intersection) {
}


Color Object::getColor() const {
  return this->color;
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
