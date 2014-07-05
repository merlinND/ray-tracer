#include <iostream>
using namespace std;

#include "Renderer.h"

/**
 * Default constructor
 */
Renderer::Renderer(Scene & s, Camera & c)
  : scene(s), camera(c) {
}

/**
 * Destructor
 */
Renderer::~Renderer() {

}

/**
 * Render the `this->scene` from the `this->camera` point of view
 * @TODO: return an image
 */
void Renderer::render() {
  cout << "Rendering scene " << this->scene.getTitle() << endl;
  for(int i = 0; i < scene.lightSources.size(); ++i) {
    cout << "> light of color " << scene.lightSources[0]->color << endl;
  }
  for(int i = 0; i < scene.objects.size(); ++i) {
    cout << "> object of color " << scene.objects[0]->material.color << endl;
  }
}
