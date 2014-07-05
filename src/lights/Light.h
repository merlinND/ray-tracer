#ifndef LIGHT_H
#define LIGHT_H

#include "../types.h"
#include "../Color.h"
#include "../Ray.h"

/**
 * Abstract class, parent of all light types
 */
class Light {
public:
  Color color;

  /** Constructor */
  Light(Color const & c = Color(1, 1, 1));


  /**
   * @return Whether or not the ray gets to the light source
   */
  virtual bool intersects(Ray const & ray) = 0;

  void setColor(Color const & c);

protected:

};

#endif
