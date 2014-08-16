#include <iostream>
#include <time.h>
using namespace std;

#include "types.h"
#include "util/mersenneTwister.h"
#include "image_output.h"

#include "scenes/ShadowsTestScene.h"

#include "renderer/Camera.h"
#include "renderer/Renderer.h"

#include "main.h"

// TODO: rename constructor parameters to use more explicit names

int main(int argc, char const *argv[])
{
  // ----- Init
  init_genrand(time(0));

  // ----- Setup scene
  ShadowsTestScene world;

  // ----- Place camera
  Camera camera(Point(4, 4, 4), ORIGIN);
  cout << "Camera view matrix:" << endl;
  cout << camera.viewMatrix << endl << endl;

  // ----- Start rendering
  Renderer r(world, camera);
  cout << "Camera default aspect ratio: " << Camera::DEFAULT_ASPECT_RATIO << endl << endl;
  Image image(160, 90);
  // Image image(320, 180);
  // Image image(711, 400);
  r.render(image);

  // ----- Output image buffer to a file
  writeImage(image, "./bin/random.jpg");

  return 0;
}
