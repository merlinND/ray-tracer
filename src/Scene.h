#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "lights/Light.h"
#include "geometry/Object.h"

class Scene
{
public:
  std::vector<Light *> lightSources;
  std::vector<Object *> objects;

  Scene();
  virtual ~Scene();

  void addObject(Object * object);
  void addLightSource(Light * light);
  std::string getTitle();

protected:
  std::string title;
};

#endif
