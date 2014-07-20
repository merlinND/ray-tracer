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

Material const Material::PLASTIC = Material();
