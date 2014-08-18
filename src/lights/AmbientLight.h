#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "../types.h"
#include "../renderer/Color.h"
#include "../renderer/Ray.h"
#include "Light.h"

/**
 * Ambient (omnipresent) light.
 */
class AmbientLight : public Light {
public:
  /** Constructors */
  AmbientLight(float i = 0.25, Color const & c = Light::DEFAULT_COLOR);


protected:
  /**
   * Ambient light is omnipresent, therefore it always
   * participates with the same intensity
   */
  virtual float computeParticipation(Scene const & scene, Ray const & lightRay);
};

#endif
