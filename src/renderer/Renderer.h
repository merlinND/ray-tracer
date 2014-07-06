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
   * Main algorithm
   * Determine the color taken by a ray
   * thrown in this scene
   */
  Color castRay(Ray const & ray, float intensity) const;

  /**
   * Compute the light color at a point of intersection
   * between a Ray and an Object
   */
  Color computeColor(Ray const & ray,
                     Object const & object,
                     Intersection const & intersection,
                     float intensity) const;
};

#endif
