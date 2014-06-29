#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Camera.h"

class Renderer
{
public:
  Renderer(Scene & s, Camera & c);
  virtual ~Renderer();

  void render();

protected:
  Scene & scene;
  Camera & camera;

};

#endif
