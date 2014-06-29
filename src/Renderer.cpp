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
}
