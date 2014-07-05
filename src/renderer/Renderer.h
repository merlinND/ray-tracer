#ifndef RENDERER_H
#define RENDERER_H

#include "../scenes/Scene.h"
#include "Camera.h"
#include "Image.h"

class Renderer
{
public:
  Renderer(Scene & s, Camera & c);
  virtual ~Renderer();

  /**
   * Render the `scene` from point of view `c`
   * and write the result in `image`
   * @param image
   */
  void render(Image & image);

protected:
  Scene & scene;
  Camera & camera;

};

#endif
