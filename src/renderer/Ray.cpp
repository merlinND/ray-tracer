#include "Ray.h"

float const Ray::DEFAULT_REFRACTION_INDEX = 1;

Ray::Ray(Point f, Vec d, float n)
  : from(f), direction(d.normalized()), refractionIndex(n) {

}
