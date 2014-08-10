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
}
