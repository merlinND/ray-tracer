#ifndef LIGHT_H
#define LIGHT_H

#include "../types.h"
#include "../scenes/Scene.h"
#include "../renderer/Color.h"
#include "../renderer/Ray.h"

/**
 * Abstract class, parent of all light types
 */
class Light {
public:
  static Color const DEFAULT_COLOR;
  /** Minimal value of light participation */
  static float const EPSILON;

  /** Constructor */
  Light(float i = 1, Color const & c = DEFAULT_COLOR);


  /**
   * @param scene
   * @param target
   * @return How much of this light source is visible at this point
   */
  virtual float getParticipation(Scene const & scene, Ray const & lightRay) = 0;

  Color getColor() const;
  void setColor(Color const & c);

protected:
  Color color;
  float intensity;
};

#endif
