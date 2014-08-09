#include "CoordinatesTestScene.h"

#include "../renderer/Color.h"
#include "../lights/AmbientLight.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

CoordinatesTestScene::CoordinatesTestScene()
  : Scene(Color(0.5, 0.5, 0.5), "Coordinates test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(1.5, 0, 4.5),
                                            0.8,
                                            Color(1, 1, 1));
  addLightSource(light);

  // Objects
  Point p;
  Object * o;
  float const PI_OVER_4 = 0.785398163;

  p << 0, 0, 0;
  o = new Sphere(p, 0.35);
  o->setColor(Color(1, 1, 1));
  o->setMaterial(Material::MIRROR);
  addObject(o);

  p << 1, 0, 0;
  o = new Cube(p, 0.5);
  o->rotate(PI_OVER_4, -PI_OVER_4, -PI_OVER_4);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << 0, 1, 0;
  o = new Cube(p, 0.5);
  o->rotate(-PI_OVER_4, PI_OVER_4, -PI_OVER_4);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);

  p << 0, 0, 1;
  o = new Cube(p, 0.5);
  o->rotate(-PI_OVER_4, -PI_OVER_4, PI_OVER_4);
  o->setColor(p);
  o->setMaterial(Material::MARBLE);
  addObject(o);
}
