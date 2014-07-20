#ifndef MATERIAL_H
#define MATERIAL_H

#include "../renderer/Color.h"

/**
 * Abstract parent class for all materials
 */
class Material {
public:
  /** Basic materials */
  static Material const PLASTIC;

  /** Constructor */
  Material();

protected:

};

#endif
