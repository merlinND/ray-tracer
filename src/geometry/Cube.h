#ifndef CUBE_H
#define CUBE_H

#include "../types.h"
#include "Object.h"

class Cube : public Object {
public:
  // TODO: properties for corners (AABB)

  /** Default constructor */
  Cube();

  virtual bool intersects(Ray const & ray);

protected:

};

#endif
