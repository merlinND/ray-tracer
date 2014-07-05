#include <iostream>
#include <time.h>
using namespace std;

#include "color.h"
#include "types.h"

#include "image_output.h"
#include "scenes/TestScene.h"
#include "Camera.h"
#include "Renderer.h"
#include "Ray.h"
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
  cout << camera.viewMatrix << endl;

  // ----- Start rendering
  Renderer r(world, camera);
  r.render();

  // ----- Testing
  Cube c;
  Ray ray(ORIGIN, Vec(1, 1, 1));
  cout << "Intersection ? " << c.intersects(ray) << endl;

  // ----- Output image buffer to a file
  // TODO: write the actual result
  writeSampleImage("./bin/random.jpg");

  return 0;
}
