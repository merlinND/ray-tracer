#ifndef PUNCUTALLIGHT_H
#define PUNCUTALLIGHT_H

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

  virtual bool intersects(Ray const & ray);

protected:

};

#endif
