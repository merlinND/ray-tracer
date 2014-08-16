#include "ShadowsTestScene.h"

#include "../renderer/Color.h"
#include "../lights/AreaLight.h"
#include "../geometry/Plane.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

ShadowsTestScene::ShadowsTestScene()
  : Scene(Color(0.5, 0.5, 0.5), "Shadows test scene") {

  // Lighting
  AreaLight * light = new AreaLight(Point(0.5, -0.5, 3.5),
                                    0.5,
                                    0.8,
                                    Colors::WHITE);
  addLightSource(light);

  // Objects
  Point p;
  Object * o;

  // Walls
  p << 0, 0, -0.25;
  o = new Plane(p, Vec(0, 0, 1));
  o->setColor(Color(0, 0.7, 1));
  o->setMaterial(Material::MARBLE);
  addObject(o);
  p << -0.25, 0, 0;
  o = new Plane(p, Vec(1, 0, 0));
  o->setColor(Color(0, 0.7, 1));
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << 0.5, -0.5, 0.5;
  o = new Sphere(p, 0.35);
  o->setColor(Colors::WHITE);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << 1, 0, 0;
  o = new Cube(p, 0.5);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << 0, 1, 0;
  o = new Cube(p, 0.5);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << 0, 0, 1;
  o = new Cube(p, 0.5);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);
}
