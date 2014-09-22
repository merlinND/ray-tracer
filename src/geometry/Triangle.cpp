#include "Triangle.h"

Triangle::Triangle(Point const & vertex1, Point const & vertex2, Point const & vertex3)
  : Object((vertex1 + vertex2 + vertex3) / 3),
    p1(vertex1), p2(vertex2), p3(vertex3) {
  // TODO: precompute normal vector
  // TODO: take texture coordinates for each vertex
}

bool Triangle::computeIntersection(Ray const & ray, Intersection * intersection) {
  // TODO: triangle intersection
  // TODO: interpolate texture coordinates from the vertices
  return false;
}
