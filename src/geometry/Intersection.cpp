#include "Intersection.h"

Intersection::Intersection()
  : object(NULL), ray(NULL), textureX(0), textureY(0) {

}
Intersection::Intersection(Object const * o, Ray const * r, float s, float t)
  : object(o), ray(r), textureX(s), textureY(t) {

}
