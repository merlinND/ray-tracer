#include <iostream>
using namespace std;

#include "Renderer.h"
#include "../geometry/Object.h"
#include "../geometry/Intersection.h"

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
      image.set(x, y, throwRay(r));
    }
  }
}

Color Renderer::throwRay(Ray const & ray) const {
  for(int i = 0; i < this->scene.objects.size(); ++i) {
    Object * o = this->scene.objects[i];
    Intersection intersection(*o, ray);

    if(o->intersects(ray, &intersection)) {
      // TODO: actual color computation with lighting, etc
      return o->getColor();
    }
    else {
      return this->scene.background;
    }
  }
}
