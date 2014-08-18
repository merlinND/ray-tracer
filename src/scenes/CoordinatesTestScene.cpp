#include "CoordinatesTestScene.h"

#include "../renderer/Color.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Plane.h"
#include "../geometry/Parallelepipoid.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

CoordinatesTestScene::CoordinatesTestScene()
  : Scene(Colors::GREY, "Coordinates test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(1.5, 0, 4.5),
                                            0.8,
                                            Colors::WHITE);
  addLightSource(light);

  // Objects
  Point p;
  Object * o;
  float const PI_OVER_4 = 0.785398163;

  p << 0, 0, 0;
  o = new Sphere(p, 0.35);
  o->setColor(Colors::WHITE);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << 1, 0, 0;
  o = new Cube(p, 0.5);
  o->rotate(PI_OVER_4, -PI_OVER_4, -PI_OVER_4);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);
  p << 1, -1.5, -0.5;
  o = new Parallelepipoid(p, 1, 0.1, 1.5);
  o->setColor(Colors::LIGHT_GREY);
  o->setMaterial(Material::MIRROR);
  o->rotate(0.5, 0, 0);
  addObject(o);

  p << 0, 1, 0;
  o = new Cube(p, 0.5);
  o->rotate(-PI_OVER_4, PI_OVER_4, -PI_OVER_4);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);
  p << -1.5, 1, -0.5;
  o = new Parallelepipoid(p, 0.1, 1, 1.5);
  o->setColor(Colors::LIGHT_GREY);
  o->setMaterial(Material::MIRROR);
  o->rotate(0, -0.5, 0);
  addObject(o);

  p << 0, 0, 1;
  o = new Cube(p, 0.5);
  o->rotate(-PI_OVER_4, -PI_OVER_4, PI_OVER_4);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);
}
