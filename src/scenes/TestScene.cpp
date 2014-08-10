#include "TestScene.h"

#include "../renderer/Color.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

TestScene::TestScene()
  : Scene(getRandomColor(), "Hello test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(0, 0, 0),
                                            0.6,
                                            Color(1, 1, 1));
  addLightSource(light);

  // Objects
  Point p(0, 0.7, 2);
  Object * o;

  o = new Cube(p, 0.8);
  o->setColor(Color(0.7, 0.2, 0.2));
  addObject(o);

  p << 0, -0.7, 2;
  o = new Sphere(p, 0.5);
  o->setColor(Color(1, 1, 1));
  o->setMaterial(Material::MIRROR);
  addObject(o);

  p << 0, 0, 0;
  o = new Cube(p, 10);
  o->setColor(Color(1, 1, 1));
  addObject(o);
}
