#include <iostream>
using namespace std;

#include "../geometry/Object.h"
#include "../geometry/Intersection.h"
#include "../lights/PunctualLight.h"

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
    cout << "> light of color " << scene.lightSources[0]->getColor() << endl;
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
      return computeColor(ray, *o, intersection, intensity);
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
  // ----- Light sources
  // TODO: support ambient light
  Color lightColor(0, 0, 0);
  for(int i = 0; i < this->scene.lightSources.size(); ++i) {
    PunctualLight * light = this->scene.lightSources[i];

    // Ray from intersection point to light source
    Vec toLight = (light->position - intersection.position).normalized();
    // TODO: support shadows by computing light obstruction
    if(true) { // !this->scene.isInterrupted(toLight)

      Color diffuse = object.getColor().cwiseProduct(light->getColor());
      // TODO: support attenuation with distance
      // TODO: support directed lights

      // TODO: check for correctness
      float cosPhi = ray.direction.dot(toLight);

      // Reflection
      if(cosPhi < 0) {
        // TODO: support diffuseReflectionCoefficient (different materials)
        diffuse *= toLight.dot(intersection.normal);

        // TODO: add specular reflection
        lightColor += diffuse;
      }
      // Transmission
      else {
        // TODO: support diffuseTransmissionCoefficient (different materials)
        diffuse *= -toLight.dot(intersection.normal);

        // TODO: add specular transmission
        lightColor += diffuse;
      }
    }
  }


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
