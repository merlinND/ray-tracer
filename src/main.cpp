#include <iostream>
#include <time.h>
using namespace std;

#include "types.h"
#include "image_output.h"

#include "scenes/TestScene.h"

#include "renderer/Camera.h"
#include "renderer/Renderer.h"

#include "main.h"

int main(int argc, char const *argv[])
{
  // ----- Init
  srand(time(0));

  // ----- Setup scene
  TestScene world;

  // ----- Place camera
  Camera camera(Point(-0.7, 0, 0.5), Point(0, 0, 1));
  cout << camera.viewMatrix << endl << endl;

  // ----- Start rendering
  Renderer r(world, camera);
  cout << "Camera default aspect ratio: " << Camera::DEFAULT_ASPECT_RATIO << endl << endl;
  Image image(200, 200);
  r.render(image);

  // ----- Output image buffer to a file
  // TODO: write the actual result
  writeImage(image, "./bin/random.jpg");

  return 0;
}
