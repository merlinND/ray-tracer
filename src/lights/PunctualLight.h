#ifndef PUNCTUALLIGHT_H
#define PUNCTUALLIGHT_H

#include "../types.h"
#include "Light.h"

/**
 * A light which has a position
 */
class PunctualLight : public Light {
public:
  Point position;

  /** Constructor */
  PunctualLight(Point const & p,
                float i = 1,
                Color const & c = Light::DEFAULT_COLOR);

  /**
   * A punctual light is either fully visible or fully obstructed.
   * This is not the case for surface lighting.
   */
  virtual float getParticipation(Scene const & scene, Ray const & lightRay);

protected:

};

#endif
