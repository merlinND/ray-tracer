#ifndef LIGHT_H
#define LIGHT_H

#include "../types.h"
#include "../renderer/Color.h"
#include "../renderer/Ray.h"

// Forward declaration to avoid circular dependencies
class Scene;

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
   * Compute the amount of participation of this light
   * towards `lightRay.from`,
   * taking into account obstruction by the scene's objects
   * and attenuation with distance.
   */
  // TODO: replace `ray` by a simple point of origin
  float getParticipation(Scene const & scene, Ray const & lightRay);

  Color getColor() const;
  void setColor(Color const & c);

protected:
  Color color;
  float intensity;

  /**
   * The amount of attenuation to the lighting effect
   * with increasing distance.
   *
   * @param source The point to be lit
   * @virtual Can optionaly be implemented differently by each kind of light
   */
  virtual float computeAttenuation(Point const & source);

  /**
   * @param scene
   * @param target
   * @return How much of this light source is visible at this point
   * @warning To be overrided by each kind of light
   */
  virtual float computeParticipation(Scene const & scene, Ray const & lightRay) = 0;
};

#endif
