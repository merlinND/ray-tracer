#include <iostream>
using namespace std;

#include "Scene.h"

/**
 * Default constructor
 */
Scene::Scene() {
  this->title = "Hello scene";
}

/**
 * Destructor
 */
Scene::~Scene() {

}

string Scene::getTitle() {
  return this->title;
}
