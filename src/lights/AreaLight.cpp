#include "../util/mersenneTwister.h"
#include "../scenes/Scene.h"
#include "AreaLight.h"

// TODO: tweak value
float const AreaLight::SAMPLING_DENSITY = 9;

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
  // Tests are organized on a grid of side `sqrt(n)`,
  // so that the whole grid contains `n` test points
  int grid = sqrt(ceil((this->side * this->side) * AreaLight::SAMPLING_DENSITY));
  int n = (grid * grid);

  // Here we assume that this light is parallel to (O, x, y)
  // TODO: cache this values to compute only once
  float halfSide = (this->side / 2.0f);
  float stride = (this->side / grid);
  Point corner = (this->position - Vec(halfSide, halfSide, 0));
  Point target;
  Ray localRay(lightRay.from, target - lightRay.from);

  for(int i = 0; i < grid; ++i) {
    for(int j = 0; j < grid; ++j) {
      // TODO: use a better random number generator
      Vec offset = Vec((j + mt_random()) * stride,
                       (i + mt_random()) * stride,
                       0);
      target = corner + offset;

      localRay.direction = (target - lightRay.from).normalized();

      if(!scene.isObstructed(localRay, target)) {
        visibleSamples++;
      }
    }
  }

  float participation = (visibleSamples / (float)n);
  return participation;
}
