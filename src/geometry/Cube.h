#ifndef CUBE_H
#define CUBE_H

#include "../types.h"
#include "Parallelepipoid.h"

class Cube : public Parallelepipoid {
public:
  /** Length of a side */
  float side;

  /**
   * @param p Position at which the cube is centered
   * @param s Length of the side of the cube
   */
  Cube(Point const & p, float s);

protected:

};

#endif
