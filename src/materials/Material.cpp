#include "Material.h"

Material::Material(float dr, float sr, float se,
                   float dt, float st,
                   float ir, float it,
                   float a,
                   float n)
  : diffuseReflection(dr), specularReflection(sr), specularExponent(se),
    diffuseTransmission(dt), specularTransmission(st),
    idealReflection(ir), idealTransmission(it),
    ambientLight(a),
    refractionIndex(n) {

}

// TODO: tweak coefficients
Material const Material::PLASTIC = Material();
Material const Material::SHINY_PLASTIC = Material(1, 1, 10);
Material const Material::GLASS = Material(1, 0.5, 5,
                                          0.5, 0.5,
                                          0.2, 0.8);
Material const Material::MIRROR = Material(0.1, 0.1, 5,
                                           0.1, 0.1,
                                           1, 0,
                                           0);
