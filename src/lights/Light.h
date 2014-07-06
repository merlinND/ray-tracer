#ifndef LIGHT_H
#define LIGHT_H

#include "../types.h"
#include "../renderer/Color.h"
#include "../renderer/Ray.h"

/**
 * Abstract class, parent of all light types
 */
class Light {
public:
  static Color const DEFAULT_COLOR;

  /** Constructor */
  Light(float i = 1, Color const & c = DEFAULT_COLOR);


  /**
   * @return Whether or not the ray gets to the light source
   */
  virtual bool intersects(Ray const & ray) = 0;

  Color getColor() const;
  void setColor(Color const & c);

protected:
  Color color;
  float intensity;
};

#endif
