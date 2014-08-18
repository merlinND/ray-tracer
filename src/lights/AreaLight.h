#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "../types.h"
#include "PunctualLight.h"

/**
 * A light which has a position and an area (square).
 */
// TODO: support different shapes
// TODO: support rotation
class AreaLight : public PunctualLight {
public:
  /** Lenght of a side in meters */
  float side;

  /**
   * Constructor
   * The light covers a square of side `s`
   * centered at `p`.
   */
  AreaLight(Point const & p,
            float s = 0.5,
            float i = 1,
            Color const & c = Light::DEFAULT_COLOR);


protected:
  /**
   * Density of samples to evaluate per unit of area (samples / m^2)
   * Can rapidly become very costly!
   */
  static float const SAMPLING_DENSITY;

  /**
   * Side of the sampling grid (in number of points).
   * There will be `grid * grid` samples taken.
   */
  int grid;
  /** Total number of samples taken */
  int n;
  /** Side of a cell from the sampling grid (in meters) */
  float stride;
  /** Top-left corner of the lighting area */
  Point corner;

  /**
   * An area light can be partly visible from a point,
   * which results in soft shadows.
   */
  virtual float computeParticipation(Scene const & scene, Ray const & lightRay);
};

#endif
