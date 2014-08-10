#include <iostream>
using namespace std;

#include "../scenes/Scene.h"
#include "../scenes/Scene.h"
#include "AreaLight.h"

// TODO: tweak value
float const AreaLight::SAMPLING_DENSITY = 4;

AreaLight::AreaLight(Point const & p, float s, float i, Color const & c)
  : PunctualLight(p, i, c), side(s) {

}

float AreaLight::getParticipation(Scene const & scene, Ray const & lightRay) {
  // This light covers a square surface.
  // Our goal is to determine which portion of this surface
  // is visible from `ray.from`.
  int visibleSamples = 0;

  // We evaluate the surface visibility by making a number of tests
  // proportional to the area.
  int n = ceil((this->side * this->side) * AreaLight::SAMPLING_DENSITY);

  // Tests are organized on a grid of side `sqrt(n)`,
  // so that the whole grid contains `n` test points
  // TODO: Monte-Carlo sampling
  int grid = sqrt(n);
  // Here we assume that this light is parallel to (O, x, y)
  // TODO: cache this values to compute only once
  float halfSide = (this->side / 2.0f);
  float stride = (this->side / grid);
  Point corner = (this->position - Vec(halfSide, halfSide, 0));
  Point target = corner;
  Ray localRay(lightRay.from, target - lightRay.from);

  for(int i = 0; i < grid; ++i) {
    for(int j = 0; j < grid; ++j) {
      localRay.direction = (target - lightRay.from).normalized();

      if(!scene.isObstructed(localRay, target)) {
        visibleSamples++;
      }

      target[0] += stride;
    }
    target[0] -= side;
    target[1] += stride;
  }

  float participation = (visibleSamples / (float)n);
  return participation;
}
