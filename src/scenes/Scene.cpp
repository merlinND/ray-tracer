#include <string>
using namespace std;

#include "Scene.h"

/**
 * Default constructor
 */
Scene::Scene(Color const & bg, string title)
  : background(bg), title(title) {

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

bool Scene::intersects(Ray const & ray, Intersection * intersection) const {
  // Distance to the closest intersection encountered so far
  float minD2 = -1;

  // For each object of the scene
  for(uint i = 0; i < this->objects.size(); ++i) {
    Object * o = this->objects[i];

    // If we're not interested in intersection data, return immediately
    if(intersection == NULL && o->intersects(ray, NULL)) {
      return true;
    }
    else {
      Intersection data(o, &ray);
      if(o->intersects(ray, &data)) {
        // Remember the closest intersection only
        float d2 = (data.position - ray.from).squaredNorm();
        if(d2 < minD2 || minD2 < Object::EPSILON) {
          minD2 = d2;
          *intersection = data;
        }
      }
    }
  }

  if(minD2 < Object::EPSILON) {
    return false;
  }
  return true;
}

bool Scene::isObstructed(Ray const & ray, Point destination) const {
  Intersection data;
  bool hasIntersection = intersects(ray, &data);
  if(!hasIntersection) {
    return false;
  }

  // The intersection could still happen further than `destination`
  float dToDestination = (destination - ray.from).squaredNorm();
  float dToIntersection = (data.position - ray.from).squaredNorm();
  return (dToDestination > dToIntersection);
}
