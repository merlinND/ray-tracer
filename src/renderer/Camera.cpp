#include <Eigen/Geometry>
#include <cmath>

#include "Camera.h"

Point const Camera::DEFAULT_POSITION = Point();
Point const Camera::DEFAULT_LOOK_AT = Point(0, 0, 1);
float const Camera::DEFAULT_DISTANCE = 100;
float const Camera::DEFAULT_FOV = 0.785398163;
float const Camera::DEFAULT_ASPECT_RATIO = (16.f / 9.f);

Camera::Camera(Point const & p, Point const & l, float distance, float fieldOfView, float ratio)
  : position(p), lookAt(l),
    d(distance), fov(fieldOfView), aspectRatio(ratio) {

  computeViewMatrix();

  // In camera coordinates, screen is centered in (0, 0, d)
  this->screenWidth = 2 * d * tan(this->fov / 2);
  this->screenHeight = this->screenWidth / this->aspectRatio;
}

Ray Camera::getRay(float rx, float ry) {
  // rx == 0 => left
  // ry == 0 => top

  // We start by working in camera coordinates
  float x = (this->screenWidth / 2.f) - (rx * this->screenWidth);
  float y = (this->screenHeight / 2.f) - (ry * this->screenHeight);
  VecH target = VecH(x, y, this->d, 1);

  // Go back to world coordinates
  VecH d = this->viewMatrix * target;
  // Apply homogeneous coordinate
  Vec direction = d.block<3, 1>(0, 0) / d[3];

  return Ray(this->position, direction);
}

void Camera::computeViewMatrix() {
  // By default: identity matrix
  this->viewMatrix = Eigen::Matrix4f::Identity();

  // ----- Translation
  this->viewMatrix.block<3, 1>(0, 3) = this->position;

  // ----- Rotation
  // Going out from the eyes of the camera towards `lookAt`
  Vec w = (this->lookAt - this->position);
  // Towards the left hand of the camera
  Vec u;
  // Towards the "hat" of the camera
  Vec v;
  if(w[0] != 0 || w[1] != 0)
    u = - w.cross(Vec(0, 0, 1));
  else
    u = - w.cross(Vec(0, 1, 0));
  v = w.cross(u);

  this->viewMatrix.block<3,1>(0, 0) = u.normalized();
  this->viewMatrix.block<3,1>(0, 1) = v.normalized();
  this->viewMatrix.block<3,1>(0, 2) = w.normalized();

  // ----- Perspective
  this->viewMatrix(3, 2) = (1 / this->d);
}
