#include "RefractionTestScene.h"

#include "../renderer/Color.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

RefractionTestScene::RefractionTestScene()
  : Scene(Colors::WHITE, "Refraction test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(0, -2, 0),
                                            0.6,
                                            Colors::WHITE);
  addLightSource(light);

  Point p;
  Object * o;

  // Walls
  p << 0.5, -3, -2.5;
  o = new Cube(p, 20);
  o->setColor(Color(0.5, 0.75, 0.5));
  o->setMaterial(Material::PLASTIC);
  addObject(o);

  // Objects
  p = ORIGIN;
  o = new Sphere(p, 1);
  o->setColor(Colors::BLACK);
  o->setMaterial(Material::GLASS);
  // o->rotate(0, 0.628318531, 0.628318531);
  addObject(o);

  p << -3, -1.5, -1.5;
  o = new Cube(p, 1);
  o->setColor(Color(0.5, 0.75, 1));
  o->setMaterial(Material::PLASTIC);
  addObject(o);
}
