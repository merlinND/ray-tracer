#include "RefractionTestScene.h"

#include "../renderer/Color.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

RefractionTestScene::RefractionTestScene()
  : Scene(Colors::WHITE, "Refraction test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(4, 0, 4),
                                            0.6,
                                            Colors::WHITE);
  addLightSource(light);

  Point p;
  Object * o;

  // Walls
  p << 0.5, -1, -0.5;
  o = new Cube(p, 10);
  o->setColor(Color(0.5, 0.75, 0.5));
  o->setMaterial(Material::PLASTIC);
  addObject(o);

  // Objects
  p = ORIGIN;
  o = new Sphere(p, 1);
  o->setColor(Colors::BLUE);
  o->setMaterial(Material::GLASS);
  o->rotate(0, 0.628318531, 0.628318531);
  addObject(o);
}
