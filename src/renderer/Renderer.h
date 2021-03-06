#ifndef RENDERER_H
#define RENDERER_H

#include "../scenes/Scene.h"
#include "Camera.h"
#include "Image.h"

class Renderer
{
public:
  Renderer(Scene & s, Camera & c);

  /**
   * Render the `scene` from point of view `c`
   * and write the result in `image`
   * @param image
   */
  void render(Image & image);

protected:
  Scene & scene;
  Camera & camera;

  /**
   * Value of intensity under which we stop considering
   * a ray's contribution to the color.
   */
  static float const MIN_INTENSITY;
  /**
   * Oversampling period: number of rays to cast per pixel, per axis
   * E.g. a period of 3 will generate 9 samples per pixel
   */
  static uint const OVERSAMPLING_PERIOD;
  /**
   * Square of OVERSAMPLING_PERIOD
   * (computed only once for efficiency)
   */
  static uint const OVERSAMPLING_PERIOD2;
  /**
   * Minimal squared difference in color between two adjacent pixels
   * that will trigger oversampling.
   */
  static float const OVERSAMPLING_THRESHOLD;
  /**
   * Figure out if any neighboring pixel is too different
   * from the one at `x`, `y` (i.e. their difference
   * goes above the oversampling threshold).
   */
  bool shouldOversample(Image const & image, int x, int y);

  /**
   * After a first pass with primary rays only, go through the
   * image again and detect differences (edges, etc).
   * At these pixels, oversample to attenuate the differences.
   */
  void oversamplingPass(Image & image);

  /**
   * Main algorithm
   * Determine the color taken by a ray
   * thrown in this scene
   */
  Color castRay(Ray const & ray, float intensity) const;

  /**
   * Compute the light color at a point of intersection
   * between a Ray and an Object
   */
  Color computeColor(Intersection const & intersection,
                     float intensity) const;
};

#endif
