#include "TexturesTestScene.h"

#include "../renderer/Color.h"
#include "../lights/PunctualLight.h"
#include "../lights/AreaLight.h"

#include "../textures/GridTexture.h"
#include "../textures/ImageTexture.h"

#include "../geometry/Plane.h"
#include "../geometry/Cube.h"
#include "../geometry/Parallelepipoid.h"
#include "../geometry/Sphere.h"

TexturesTestScene::TexturesTestScene()
  : Scene(Colors::WHITE, "Texture test scene") {

  // Lighting
  PunctualLight * light = new PunctualLight(Point(0, 0, 4),
                                            0.6,
                                            Colors::WHITE);
  addLightSource(light);

  // Objects
  Point p;
  Object * o;

  // Walls
  p << 0, 0, -3;
  o = new Plane(p, Vec(0, 0, 1));
  // o->setTexture(new GridTexture());
  addObject(o);

  p << 0, 0, 0;
  o = new Sphere(p, 1);
  o->setTexture(new ImageTexture("./res/textures/orange-sand.jpg"));
  o->rotate(- PI / 2.f, 0.1f, 0);
  addObject(o);

  // p << -2.5, 0, 0;
  // o = new Parallelepipoid(p, 0.1, 5, 5);
  // o->setMaterial(Material::MIRROR);
  // o->rotate(0, -0.4, 0);
  // addObject(o);

  // p << -2, 0, 0;
  // o = new Sphere(p, 1);
  // o->setTexture(new ImageTexture("./res/textures/rock.jpg"));
  // addObject(o);

  // p << 0.1, 0.1, 0;
  // o = new Cube(p, 1.2);
  // o->setTexture(new ImageTexture("./res/textures/rubiks-cube.jpg"));
  // addObject(o);

}
