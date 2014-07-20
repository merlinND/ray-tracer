#include "TestScene.h"

#include "../renderer/Color.h"
#include "../lights/AmbientLight.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

TestScene::TestScene()
  : Scene(getRandomColor(), "Hello test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(0, 0.5, -1),
                                            1.5,
                                            Color(0.3, 1, 1));
  addLightSource(light);

  // Objects
  Point p(0, 0, 3);
  addObject(new Cube(p, 0.5));
  p[2] = 1;
  addObject(new Sphere(p, 0.2));
}
