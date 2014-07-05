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
  Camera camera;
  cout << camera.viewMatrix << endl << endl;
  cout << "Top left: " << camera.getRay(0, 0) << endl;
  cout << "Top right: " << camera.getRay(1, 0) << endl << endl;
  cout << "Middle: " << camera.getRay(0.5, 0.5) << endl << endl;
  cout << "Bottom left: " << camera.getRay(0, 1) << endl;
  cout << "Bottom right: " << camera.getRay(1, 1) << endl << endl;

  // ----- Start rendering
  Renderer r(world, camera);
  r.render();

  // ----- Output image buffer to a file
  // TODO: write the actual result
  writeSampleImage("./bin/random.jpg");

  return 0;
}
