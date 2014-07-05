#include <iostream>
using namespace std;

#include "lights/AmbientLight.h"
#include "geometry/Cube.h"

#include "Scene.h"

/**
 * Default constructor
 */
Scene::Scene()
  : title("Hello scene") {

  addLightSource(new AmbientLight(Color(1, 0, 0)));
  addObject(new Cube());
}

/**
 * Destructor
 */
Scene::~Scene() {
  for(int i = 0; i < this->lightSources.size(); ++i) {
    delete this->lightSources[i];
  }
  for(int i = 0; i < this->objects.size(); ++i) {
    delete this->objects[i];
  }
}

void Scene::addObject(Object * object) {
  this->objects.push_back(object);
}
void Scene::addLightSource(Light * light) {
  this->lightSources.push_back(light);
}

string Scene::getTitle() {
  return this->title;
}
