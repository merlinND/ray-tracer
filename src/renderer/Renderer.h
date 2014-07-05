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
   * Main algorithm
   * Determine the color taken by a ray
   * thrown in this scene
   */
  Color throwRay(Ray ray);
};

#endif
