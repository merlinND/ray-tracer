#include <iostream>
using namespace std;

#include "Renderer.h"
#include "../geometry/Object.h"
#include "../geometry/Intersection.h"

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
    Intersection intersection(*o, ray);

    if(o->intersects(ray, &intersection)) {
      return computeColor(ray, *o, intensity);
    }
    else {
      return this->scene.background;
    }
  }
}

Color Renderer::computeColor(Ray const & ray,
                             Object const & object,
                             //Intersection const & intersection,
                             float intensity) const {
  // ----- Light sources
  Color lightColor = object.getColor();
  /*
  foreach(this->scene->lightSources) {
    // Ray from intersection point to light source
    Ray toLight(intersection.position, lightSource.position - intersection.position);
    if(!this->scene.isInterrupted(toLight)) {
      if(ray.direction.angle(toLight.direction) > (PI / 2)) {
        result += diffuse and specular reflexion;
      }
      else {
        result += diffuse and specular transmission;
      }
    }
  }
  */

  // ----- Refraction (e.g. glass)
  /*
  Ray refractionRay(intersection.position, ???);
  Color transmissionColor;
  if(!total reflection) {
    float t = object.getTransmissionCoefficient()
    transmissionColor = t * castRay(refractionRay, t * intensity);
  }
  */
  // ----- Reflection (e.g. mirror)
  /*
  Ray reflectionRay(intersection.position, ???);
  float r = object.getReflectionCoefficient();
  Color reflectionColor = r * castRay(reflectionRay, r * intensity);
  */

  return lightColor; // + transmissionColor + reflectionColor;
}
