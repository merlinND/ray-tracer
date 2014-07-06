#include <iostream>
using namespace std;

#include "Renderer.h"

// TODO: tweak value
float const Renderer::MIN_INTENSITY = 0.05;

Renderer::Renderer(Scene & s, Camera & c)
  : scene(s), camera(c) {
}

void Renderer::render(Image & image) {
  cout << "Rendering scene " << this->scene.title << endl;
  cout << "> background color " << this->scene.background << endl;
  for(int i = 0; i < scene.lightSources.size(); ++i) {
    cout << "> light of color " << scene.lightSources[0]->color << endl;
  }
  for(int i = 0; i < scene.objects.size(); ++i) {
    cout << "> object of color " << scene.objects[0]->material.color << endl;
  }

  // TODO: antialiasing by oversampling
  for(int x = 0; x < image.width; ++x) {
    for(int y = 0; y < image.height; ++y) {
      Ray r = this->camera.getRay( (x / (float)image.width), (y / (float)image.height) );
      image.set(x, y, castRay(r, 1));
    }
  }
}

Color Renderer::castRay(Ray const & ray, float intensity) const {
  if(intensity < Renderer::MIN_INTENSITY) {
    // TODO: is this the correct neutral color?
    return Color(0, 0, 0);
  }

  for(int i = 0; i < this->scene.objects.size(); ++i) {
    Object * o = this->scene.objects[i];
    if(o->intersects(ray)) {
      // TODO: actual color computation with lighting, etc
      return o->getColor();
    }
    else {
      return this->scene.background;
    }
  }
}

Color Renderer::computeColor(Ray const & ray,
                             Object const & object,
                             Intersection const & intersection,
                             float intensity) const {

}
