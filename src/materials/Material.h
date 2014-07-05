#ifndef MATERIAL_H
#define MATERIAL_H

#include "../renderer/Color.h"

/**
 * Abstract parent class for all materials
 */
class Material {
public:
  Color color;

  /** Constructor */
  Material(Color const & c);

protected:

};

#endif
