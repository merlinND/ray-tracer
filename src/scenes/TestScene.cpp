#include "TestScene.h"

#include "../renderer/Color.h"
#include "../lights/AmbientLight.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Cube.h"

TestScene::TestScene()
  : Scene(getRandomColor(), "Hello test scene") {

  // Lighting
  addLightSource(new PunctualLight(Point(-10, 10, 0)));

  // Objects
  Point p(0, 0, 1);
  addObject(new Cube(p, 0.5));
}
