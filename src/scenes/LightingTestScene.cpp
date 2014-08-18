#include "LightingTestScene.h"

#include "../renderer/Color.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Plane.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

LightingTestScene::LightingTestScene()
  : Scene(Color(0.5, 0.5, 0.5), "Lighting test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(1, -1, 3.5),
                                    0.8,
                                    Colors::WHITE);
  addLightSource(light);

  Point p;
  Object * o;

  // Ground
  p = ORIGIN;
  o = new Plane(p, Vec(0, 0, 1));
  o->setColor(Color(0, 0.7, 1));
  o->setMaterial(Material::PLASTIC);
  addObject(o);

  // Objects
  p << 0, 0, 0.5;
  o = new Sphere(p, 0.35);
  o->setColor(Colors::WHITE);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << -10, 0, 0.5;
  o = new Sphere(p, 0.35);
  o->setColor(Colors::WHITE);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << -30, 0, 0.5;
  o = new Sphere(p, 0.35);
  o->setColor(Colors::WHITE);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << -60, 0, 0.5;
  o = new Sphere(p, 0.35);
  o->setColor(Colors::WHITE);
  o->setMaterial(Material::MARBLE);
  addObject(o);
}
