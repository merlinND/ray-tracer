#include "TexturesTestScene.h"

#include "../renderer/Color.h"
#include "../lights/PunctualLight.h"

#include "../textures/GridTexture.h"
#include "../textures/ImageTexture.h"

#include "../geometry/Plane.h"
#include "../geometry/Cube.h"
#include "../geometry/Sphere.h"

TexturesTestScene::TexturesTestScene()
  : Scene(getRandomColor(), "Texture test scene") {

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
  o->setTexture(new GridTexture());
  addObject(o);


  p << 1, -1, 0;
  o = new Cube(p, 1);
  o->setTexture(new GridTexture(Colors::GREEN));
  addObject(o);

  p << -1, 1, 0;
  o = new Sphere(p, 0.8);
  o->setTexture(new ImageTexture("./bin/doge.jpg"));
  addObject(o);

}
