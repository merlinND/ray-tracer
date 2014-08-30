#include <iostream>
#include <time.h>
using namespace std;

#include "types.h"
#include "util/mersenneTwister.h"
#include "util/image_output.h"

#include "scenes/RefractionTestScene.h"

#include "renderer/Camera.h"
#include "renderer/Renderer.h"

#include "main.h"

// TODO: rename constructor parameters to use more explicit names

void printInfo(Camera const & camera, Scene const & scene) {
  cout << "Rendering scene " << scene.title << endl;
  cout << "> background color " << scene.background << endl;
  cout << "> ambient light of color " << scene.ambientLight.getColor() << endl;
  for(int i = 0; i < scene.lightSources.size(); ++i) {
    cout << "> light source of color " << scene.lightSources[i]->getColor() << endl;
  }
  for(int i = 0; i < scene.objects.size(); ++i) {
    cout << "> object of color " << scene.objects[i]->getColor() << endl;
  }
}

int main(int argc, char const *argv[])
{
  // ----- Init
  init_genrand(time(0));

  // ----- Setup scene
  RefractionTestScene world;

  // ----- Place camera
  Camera camera(Point(4, 4, 4), ORIGIN);

  Renderer r(world, camera);
  Image image(160, 90);
  // Image image(320, 180);
  // Image image(711, 400);

  printInfo(camera, world);

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
