#include <Eigen/Geometry>
#include <cmath>

#include "../textures/ColorTexture.h"
#include "Object.h"

float const Object::EPSILON = 0.0000000001f;
float const Object::PUSH_BACK = 0.00005f;

Color const Object::DEFAULT_COLOR = Colors::WHITE;
Material const & Object::DEFAULT_MATERIAL = Material::PLASTIC;

Object::Object(Point const & pos, Color const & c, Material const & m)
  : texture(NULL), material(&m) {
  this->setColor(c);
  this->init(pos);
}

Object::Object(Point const & pos, Texture const & tex, Material const & m)
  : texture(&tex), material(&m) {
  this->init(pos);
}

Object::~Object() {
  delete this->texture;
}

void Object::init(Point const & pos) {
  this->hasRotation = false;
  this->rotationMatrix = Eigen::Matrix3f::Identity();
  this->rotationMatrixT = Eigen::Matrix3f::Identity();
  moveTo(pos);
}

void Object::moveTo(Point const & pos) {
  this->position = pos;
}

void Object::rotate(float rx, float ry, float rz) {
  // This rotation is the composition of
  // three rotations (one along each axis).
  // We want the resulting rotation matrix to move us
  // from world coordinates to object coordinates.
  Eigen::Matrix3f r;

  if(std::abs(rx) > Object::EPSILON) {
    hasRotation = true;
    r = Eigen::Matrix3f::Identity();
    r(1, 1) = cos(rx);
    r(1, 2) = sin(rx);
    r(2, 1) = -sin(rx);
    r(2, 2) = cos(rx);

    this->rotationMatrix = r * this->rotationMatrix;
  }
  if(std::abs(ry) > Object::EPSILON) {
    hasRotation = true;
    r = Eigen::Matrix3f::Identity();
    r(0, 0) = cos(ry);
    r(0, 2) = -sin(ry);
    r(2, 0) = sin(ry);
    r(2, 2) = cos(ry);

    this->rotationMatrix = r * this->rotationMatrix;
  }
  if(std::abs(rz) > Object::EPSILON) {
    hasRotation = true;
    r = Eigen::Matrix3f::Identity();
    r(0, 0) = cos(rz);
    r(0, 1) = sin(rz);
    r(1, 0) = -sin(rz);
    r(1, 1) = cos(rz);

    this->rotationMatrix = r * this->rotationMatrix;
  }

  this->rotationMatrixT = this->rotationMatrix;
  this->rotationMatrixT.transposeInPlace();
}

bool Object::intersects(Ray const & ray, Intersection * intersection) {
  // We first move the ray to object space before computing the intersection
  Ray localRay(ray.from - this->position, ray.direction);

  if(this->hasRotation) {
    localRay.from = this->rotationMatrix * localRay.from;
    // No need to normalize because the rotation matrix already is
    localRay.direction = this->rotationMatrix * localRay.direction;
  }

  bool hasIntersection = computeIntersection(localRay, intersection);

  // Move back to world coordinates
  if(intersection != NULL) {
    if(this->hasRotation) {
      intersection->position = (this->rotationMatrixT * intersection->position);
      intersection->normal = (this->rotationMatrixT * intersection->normal);
    }
    intersection->position += this->position;
  }

  return hasIntersection;
}


Color Object::getColor(Intersection const & intersection) const {
  return this->texture->getColor(intersection.textureX, intersection.textureY);
}
void Object::setColor(Color const & color) {
  this->setTexture(new ColorTexture(color));
}

Texture const & Object::getTexture() const {
  return *(this->texture);
}
void Object::setTexture(Texture * texture) {
  if(this->texture != NULL) {
    delete this->texture;
  }
  this->texture = texture;
}

Material const & Object::getMaterial() const {
  return *(this->material);
}
void Object::setMaterial(Material const & material) {
  this->material = &material;
}
