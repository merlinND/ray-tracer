#include <iostream>
using namespace std;

#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"
#include "main.h"

int main(int argc, char const *argv[])
{
  // ----- Setup scene
  Scene world;

  // ----- Place camera
  Camera camera;

  // ----- Start rendering
  Renderer r(world, camera);
  r.render();

  // ----- Output image buffer to a file
  // TODO

  return 0;
}
