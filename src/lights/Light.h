#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#include "../types.h"
#include "../Color.h"
#include "../Ray.h"

/**
 * Abstract class, parent of all light types
 */
class Light {
public:
  Point position;
  Color color;

  /** Constructor */
  Light(Point p);


  /**
   * @return Whether or not the ray gets to the light source
   */
  virtual bool intersects(Ray const & ray) = 0;

  void setColor(Color c);

protected:

};

#endif
