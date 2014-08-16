#include "../util/mersenneTwister.h"
#include "../scenes/Scene.h"
#include "AreaLight.h"

// TODO: tweak value
float const AreaLight::SAMPLING_DENSITY = 9;

AreaLight::AreaLight(Point const & p, float s, float i, Color const & c)
  : PunctualLight(p, i, c), side(s) {

  // We evaluate the surface visibility by making a number of tests
  // proportional to the area.
  // Tests are organized on a grid of side `sqrt(n)`,
  // so that the whole grid contains `n` test points
  this->grid = sqrt(ceil((this->side * this->side) * AreaLight::SAMPLING_DENSITY));
  this->n = (grid * grid);
  this->stride = (this->side / grid);

  // Here we assume that this light is parallel to (O, x, y)
  float halfSide = (this->side / 2.0f);
  this->corner = (this->position - Vec(halfSide, halfSide, 0));
}

float AreaLight::getParticipation(Scene const & scene, Ray const & lightRay) {
  // This light covers a square surface.
  // Our goal is to determine which portion of this surface
  // is visible from `ray.from`.
  int visibleSamples = 0;

  Point target = this->corner;
  Ray localRay(lightRay.from, Vec(0, 0, 0));

  for(int i = 0; i < grid; ++i) {
    for(int j = 0; j < grid; ++j) {
      target[0] = this->corner[0] + ((j + mt_random()) * stride);
      target[1] = this->corner[1] + ((i + mt_random()) * stride);

      localRay.direction = (target - lightRay.from).normalized();

      if(!scene.isObstructed(localRay, target)) {
        visibleSamples++;
      }
    }
  }

  float participation = (visibleSamples / (float)this->n);
  return participation;
}
