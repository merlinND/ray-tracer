#include <Eigen/Geometry>

#include "Camera.h"

Point const Camera::DEFAULT_POSITION = Point();
Point const Camera::DEFAULT_LOOK_AT = Point(0, 0, 1);
float const Camera::DEFAULT_DISTANCE = 2;
float const Camera::DEFAULT_FOV = 1.570796327;
float const Camera::DEFAULT_ASPECT_RATIO = (16 / 9);

Camera::Camera(Point const & p, Point const & l, float distance, float fieldOfView, float ratio)
  : position(p), lookAt(l),
    d(distance), fov(fieldOfView), aspectRatio(ratio) {

  computeViewMatrix();

  // In camera coordinates, screen is centered in (0, 0, d)
  this->screenWidth = 2 * d * tan(this->fov / 2);
  this->screenHeight = this->screenWidth / this->aspectRatio;
}

Camera::~Camera() {

}

void Camera::computeViewMatrix() {
  // By default: identity matrix
  this->viewMatrix = Eigen::Matrix4f::Identity();

  // ----- Translation
  this->viewMatrix.block<3, 1>(0, 3) = this->position;

  // ----- Rotation
  // TODO: Check we're not inverting axes in some cases
  // Going out from the eyes of the camera to `lookAt`
  Vec w = (this->lookAt - this->position);
  // Towards the "hat" of the camera
  Vec u;
  // Towards the right hand of the camera
  Vec v;
  if(w[0] != 0 && w[1] != 0) {
    u = Vec(0, 0, 1).cross(w);
    v = u.cross(w);
  }
  else {
    u = Vec(0, 1, 0).cross(w);
    v = - u.cross(w);
  }

  this->viewMatrix.block<3,1>(0, 0) = u.normalized();
  this->viewMatrix.block<3,1>(0, 1) = v.normalized();
  this->viewMatrix.block<3,1>(0, 2) = w.normalized();

  // ----- Perspective
  this->viewMatrix(3, 2) = (1 / this->d);
}
