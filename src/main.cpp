#include <iostream>
using namespace std;

#include "image_output.h"
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
  // TODO: write the actual result
  writeSampleImage("./bin/random.jpg");

  return 0;
}
