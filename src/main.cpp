#include <iostream>
#include <time.h>
using namespace std;

#include "types.h"
#include "image_output.h"

#include "scenes/TestScene.h"

#include "renderer/Color.h"
#include "renderer/Ray.h"
#include "renderer/Camera.h"
#include "renderer/Renderer.h"

#include "lights/Light.h"

#include "geometry/Cube.h"

#include "main.h"

int main(int argc, char const *argv[])
{
  // ----- Init
  srand(time(0));

  // ----- Setup scene
  TestScene world;

  // ----- Place camera
  Camera camera(Point(1, 0.1, 0.1), Point(0, 0, 1));
  cout << camera.viewMatrix << endl << endl;
  cout << "Top left: " << camera.getRay(0, 0) << endl;
  cout << "Top right: " << camera.getRay(1, 0) << endl << endl;
  cout << "Middle: " << camera.getRay(0.5, 0.5) << endl << endl;
  cout << "Bottom left: " << camera.getRay(0, 1) << endl;
  cout << "Bottom right: " << camera.getRay(1, 1) << endl << endl;

  // ----- Start rendering
  Renderer r(world, camera);
  cout << "Camera default aspect ratio: " << Camera::DEFAULT_ASPECT_RATIO << endl;
  Image image;
  r.render(image);

  // ----- Output image buffer to a file
  // TODO: write the actual result
  writeImage(image, "./bin/random.jpg");

  return 0;
}
