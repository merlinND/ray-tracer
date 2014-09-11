#ifndef TYPES_H
#define TYPES_H

#include <Eigen/Core>

typedef Eigen::Vector4f VecH;
typedef Eigen::Vector3f Vec;
typedef Eigen::Vector2f Vec2;
typedef Vec Point;

#define ORIGIN Point(0, 0, 0)

#define PI 3.14159265358979323846f

/**
 * Signum helper function
 * @see http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
 */
inline float signum(float val) {
  return ((0.f < val) - (val < 0.f));
}

#endif
