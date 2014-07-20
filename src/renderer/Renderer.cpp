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

  Intersection closestIntersection;
  float minD2 = -1;

  // For each object of the scene
  for(uint i = 0; i < this->scene.objects.size(); ++i) {
    Object * o = this->scene.objects[i];
    Intersection intersection(o, &ray);

    if(o->intersects(ray, &intersection)) {
      // Remember the closest intersection only
      float d2 = (intersection.position - ray.from).squaredNorm();
      if(d2 < minD2 || minD2 < Object::EPSILON) {
        minD2 = d2;
        closestIntersection = intersection;
      }
    }
  }

  if(minD2 < Object::EPSILON) {
    return this->scene.background;
  }
  else {
    return computeColor(closestIntersection, intensity);
  }
}

Color Renderer::computeColor(Intersection const & intersection,
                             float intensity) const {
  Ray const * ray = intersection.ray;
  Object const * object = intersection.object;

  // ----- Light sources
  // TODO: support ambient light
  Color lightColor(0, 0, 0);
  for(int i = 0; i < this->scene.lightSources.size(); ++i) {
    PunctualLight * light = this->scene.lightSources[i];

    // Ray from intersection point to light source
    Vec toLight = (light->position - intersection.position).normalized();
    // TODO: support shadows by computing light obstruction
    if(true) { // !this->scene.isInterrupted(toLight)
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
