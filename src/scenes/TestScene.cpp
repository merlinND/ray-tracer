#include "TestScene.h"

#include "../lights/AmbientLight.h"
#include "../geometry/Cube.h"

TestScene::TestScene()
  : Scene(Color(0, 1, 0), "Hello test scene") {
  addLightSource(new AmbientLight(Color(1, 0, 0)));

  Point p(0, 0, 5);
  addObject(new Cube(p, 0.5));
}
