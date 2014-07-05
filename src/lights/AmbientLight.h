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
  AmbientLight();
  AmbientLight(Color const & c);

  /**
   * Ambient light is omnipresent, therefore it intersects with everything
   */
  virtual bool intersects(Ray const & ray);

protected:

};

#endif
