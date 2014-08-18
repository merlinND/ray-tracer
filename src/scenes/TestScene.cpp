#include "TestScene.h"

#include "../renderer/Color.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

TestScene::TestScene()
  : Scene(getRandomColor(), "Hello test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(0, 0, 4),
                                            0.6,
                                            Colors::WHITE);
  addLightSource(light);

  // Objects
  Point p;
  Object * o;

  // Walls
  p << 0, 0, 0;
  o = new Cube(p, 15);
  o->setColor(Colors::WHITE);
  addObject(o);


  p << 1, -1, 0;
  o = new Cube(p, 1);
  o->setColor(Color(0.7, 0.2, 0.2));
  addObject(o);

  p << -1, 1, 0;
  o = new Sphere(p, 0.8);
  o->setColor(Colors::WHITE);
  o->setMaterial(Material::MIRROR);
  addObject(o);

}
