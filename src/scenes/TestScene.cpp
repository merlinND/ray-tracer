#include "TestScene.h"

#include "../renderer/Color.h"
#include "../lights/AmbientLight.h"
#include "../geometry/Cube.h"

TestScene::TestScene()
  : Scene(getRandomColor(), "Hello test scene") {
  addLightSource(new AmbientLight(Color(1, 0, 0)));

  Point p(0, 0, 1);
  addObject(new Cube(p, 0.5));
}
