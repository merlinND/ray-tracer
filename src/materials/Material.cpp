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
Material const Material::MARBLE = Material(1, 1, 20);
Material const Material::GLASS = Material(0.1, 0.99, 30,
                                          0.9, 0.9,
                                          0, 0.99,
                                          0,
                                          1.6);
Material const Material::MIRROR = Material(0.3, 0.3, 5,
                                           0.1, 0.1,
                                           0.9, 0,
                                           0);
