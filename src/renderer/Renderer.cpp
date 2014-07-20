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
  cout << "> ambient light of color " << this->scene.ambientLight.getColor() << endl;
  for(int i = 0; i < scene.lightSources.size(); ++i) {
    cout << "> light source of color " << scene.lightSources[i]->getColor() << endl;
  }
  for(int i = 0; i < scene.objects.size(); ++i) {
    cout << "> object of color " << scene.objects[i]->material.color << endl;
  }

  for(int x = 0; x < image.width; ++x) {
    for(int y = 0; y < image.height; ++y) {
      // TODO: adaptative oversampling
      int nSamples = 5;
      float ix = (x / (float)image.width),
            iy = (y / (float)image.height),
            dx = (1 / (float)image.width) / (float)nSamples,
            dy = (1 / (float)image.height) / (float)nSamples;
      Color accumulator(0, 0, 0);

      for(int i = 0; i < nSamples; ++i) {
        Ray r = this->camera.getRay(ix + i * dx, iy + i * dy);
        accumulator += castRay(r, 1);
      }

      image.set(x, y, accumulator / nSamples);
    }
  }
}

Color Renderer::castRay(Ray const & ray, float intensity) const {
  if(intensity < Renderer::MIN_INTENSITY) {
    // TODO: is this the correct neutral color?
    return Color(0, 0, 0);
  }

  Intersection intersection;
  bool intersects = this->scene.intersects(ray, &intersection);

  if(intersects) {
    return computeColor(intersection, intensity);
  }
  else {
    return this->scene.background;
  }
}

Color Renderer::computeColor(Intersection const & intersection,
                             float intensity) const {
  Ray const * ray = intersection.ray;
  Object const * object = intersection.object;

  // ----- Ambient light
  // TODO: add ambient reflection parameter (material)
  Color lightColor = 1 * this->scene.ambientLight.getColor()
                      .cwiseProduct(object->getColor());

  // ----- Light sources
  for(int i = 0; i < this->scene.lightSources.size(); ++i) {
    PunctualLight * light = this->scene.lightSources[i];

    // Ray from intersection point to light source
    Vec toLight = (light->position - intersection.position).normalized();
    Ray lightRay(intersection.position, toLight);

    // Intersection data;
    if(!this->scene.isObstructed(lightRay, light->position)) {
      // TODO: support attenuation with distance
      // TODO: support directed lights
      // TODO: support different coefficients per material
      Color diffuse = object->getColor();
      Color specular(0, 0, 0);

      float cosPhi = ray->direction.dot(toLight);
      if(cosPhi < 0) {
        // ----- Reflection
        diffuse *= 1 * toLight.dot(intersection.normal);

        /**
         * Vector symetric to the direction of observation
         * relative to the normal at the point of intersection.
         * It corresponds to the "preferred" direction of reflexion
         * according to Descartes' laws
         */
        Vec symetric = 2 * (intersection.normal.dot(-ray->direction) * intersection.normal) + ray->direction;
        float cosAlpha = toLight.dot(symetric);
        specular = 0.4 * Color(1, 1, 1) * pow(cosAlpha, 5);
      }
      else {
        // ----- Transmission
        diffuse *= 1 * -toLight.dot(intersection.normal);

        // TODO: support specular transmission (depends on the refraction indices of the mediums)
      }

      lightColor += light->getColor().cwiseProduct(diffuse + specular);
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
