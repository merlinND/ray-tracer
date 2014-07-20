#include "Intersection.h"

Intersection::Intersection()
  : object(NULL), ray(NULL) {

}
Intersection::Intersection(Object const * o, Ray const * r)
  : object(o), ray(r) {

}
