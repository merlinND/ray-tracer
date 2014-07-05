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
 */
void Renderer::render(Image & image) {
  cout << "Rendering scene " << this->scene.title << endl;
  cout << "> background color " << this->scene.background << endl;
  for(int i = 0; i < scene.lightSources.size(); ++i) {
    cout << "> light of color " << scene.lightSources[0]->color << endl;
  }
  for(int i = 0; i < scene.objects.size(); ++i) {
    cout << "> object of color " << scene.objects[0]->material.color << endl;
  }

  // TODO: throw rays and write resulting colors to the image
  // TODO: antialiasing by oversampling
}
