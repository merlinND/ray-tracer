#include "Camera.h"

float const Camera::DEFAULT_DISTANCE = 2;
float const Camera::DEFAULT_FOV = 1.570796327;
Point const Camera::DEFAULT_POSITION = Point();
Point const Camera::DEFAULT_LOOK_AT = Point(0, 0, 1);

Camera::Camera(Point const & p, Point const & l, float distance, float fieldOfView)
  : position(p), lookAt(l), d(distance), fov(fieldOfView) {

  computeViewMatrix();
}

Camera::~Camera() {

}

void Camera::computeViewMatrix() {
  // TODO
}
