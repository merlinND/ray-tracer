#include "TestScene.h"

#include "../renderer/Color.h"
#include "../lights/AmbientLight.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Cube.h"

TestScene::TestScene()
  : Scene(getRandomColor(), "Hello test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(1, 0.5, 1),
                                            2.5,
                                            Color(0.3, 1, 1));
  addLightSource(light);

  // Objects
  Point p(0, 0, 1);
  addObject(new Cube(p, 0.5));
  p << 0, 0.5, 1;
  addObject(new Sphere(p, 0.4));
}
