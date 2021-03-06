#ifndef MATERIAL_H
#define MATERIAL_H

#include "../renderer/Color.h"

/**
 * Abstract parent class for all materials
 */
class Material {
public:
  /**
   * The following are coefficients defining the reaction of
   * different kinds of materials (glass, mirror, plastic, ...)
   * to light. Each coefficient is in [0, 1].
   */
  float diffuseReflection, specularReflection, specularExponent,
        diffuseTransmission, specularTransmission, specularTransmissionExponent,
        idealReflection, idealTransmission,
        ambientLight,
        refractionIndex;

  // TODO: support shine color

  /** Basic materials */
  static Material const PLASTIC;
  static Material const MARBLE;
  static Material const GLASS;
  static Material const MIRROR;

  /** Constructor */
  Material(float dr = 1, float sr = 0.2, float se = 5,
           float dt = 0.5, float st = 0.5, float ste = 15,
           float ir = 0, float it = 0,
           float a = 1,
           float n = 1);

protected:

};

#endif
