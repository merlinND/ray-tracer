#include <iostream>
#include <time.h>
using namespace std;

#include "types.h"
#include "util/mersenneTwister.h"
#include "image_output.h"

#include "scenes/LightingTestScene.h"

#include "renderer/Camera.h"
#include "renderer/Renderer.h"

#include "main.h"

// TODO: rename constructor parameters to use more explicit names

int main(int argc, char const *argv[])
{
  // ----- Init
  init_genrand(time(0));

  // ----- Setup scene
  LightingTestScene world;

  // ----- Place camera
  Camera camera(Point(3, 0, 1.3), Point(-20, 0, 0));
  cout << "Camera view matrix:" << endl;
  cout << camera.viewMatrix << endl << endl;

  Renderer r(world, camera);
  Image image(160, 90);
  // Image image(320, 180);
  // Image image(711, 400);

  // ----- Start rendering
  clock_t begin = clock();
  r.render(image);
  double elapsed = double(clock() - begin) / CLOCKS_PER_SEC;

  // ----- Output approximative time spent
  cout << "Rendered the " << image.width << "x" << image.height;
  cout << " scene in " << elapsed << "s." << endl;

  // ----- Output image buffer to a file
  writeImage(image, "./bin/random.jpg");

  return 0;
}
