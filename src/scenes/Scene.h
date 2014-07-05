#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "../renderer/Color.h"
#include "../lights/Light.h"
#include "../geometry/Object.h"

class Scene {
public:
  std::string title;
  Color background;
  std::vector<Light *> lightSources;
  std::vector<Object *> objects;

  Scene(Color const & bg, std::string title);
  virtual ~Scene();

  void addObject(Object * object);
  void addLightSource(Light * light);

protected:
};

#endif
