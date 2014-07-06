#include <iostream>
using namespace std;

#include "Scene.h"

/**
 * Default constructor
 */
Scene::Scene(Color const & bg, string title)
  : background(bg), title(title), ambientLight(0.1) {

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
void Scene::addLightSource(PunctualLight * light) {
  this->lightSources.push_back(light);
}
