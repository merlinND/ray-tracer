#include <iostream>
using namespace std;

#include "../geometry/Object.h"
#include "../geometry/Intersection.h"
#include "../lights/PunctualLight.h"

#include "Renderer.h"

// TODO: tweak value
float const Renderer::MIN_INTENSITY = 0.05;
uint const Renderer::OVERSAMPLING_PERIOD = 2;
uint const Renderer::OVERSAMPLING_PERIOD2 = Renderer::OVERSAMPLING_PERIOD * Renderer::OVERSAMPLING_PERIOD;

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
    cout << "> object of color " << scene.objects[i]->getColor() << endl;
  }

  float progress = 0;
  cout << endl << "Casting rays" << flush;

  // TODO: adaptative oversampling
  float dx = (1 / (float)image.width) / (float)Renderer::OVERSAMPLING_PERIOD,
        dy = (1 / (float)image.height) / (float)Renderer::OVERSAMPLING_PERIOD;

  for(int x = 0; x < image.width; ++x) {
    for(int y = 0; y < image.height; ++y) {
      float ix = (x / (float)image.width),
            iy = (y / (float)image.height);
      Color accumulator(0, 0, 0);

      for(int i = 0; i < Renderer::OVERSAMPLING_PERIOD; ++i) {
        for(int j = 0; j < Renderer::OVERSAMPLING_PERIOD; ++j) {
          Ray r = this->camera.getRay(ix + i * dx, iy + j * dy);
          accumulator += castRay(r, 1);
        }
      }

      image.set(x, y, accumulator / Renderer::OVERSAMPLING_PERIOD2);
    }

    float currentProgress = (x / (float)image.width);
    if(currentProgress >= progress + 0.05) {
      cout << "." << flush;
      progress = currentProgress;
    }
  }
  cout << ".done" << endl;
}

Color Renderer::castRay(Ray const & ray, float intensity) const {
  if(intensity < Renderer::MIN_INTENSITY) {
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
  Material const & mat = object->getMaterial();

  /**
   * Angle made by the vector pointing towards the observer
   * and the normal at the point of intersection
   */
  float cosTheta = intersection.normal.dot(-ray->direction);

  /**
   * Vector symmetric to the direction of observation
   * relative to the normal at the point of intersection.
   * It corresponds to the "preferred" direction of reflection
   * according to Descartes' laws
   */
  Vec symmetric = (2 * cosTheta * intersection.normal) + ray->direction;


  // ----- Ambient light
  Color lightColor = mat.ambientLight
                    * this->scene.ambientLight.getColor()
                      .cwiseProduct(object->getColor());

  // ----- Light sources
  for(int i = 0; i < this->scene.lightSources.size(); ++i) {
    PunctualLight * light = this->scene.lightSources[i];

    // Ray from intersection point to light source
    Vec toLight = (light->position - intersection.position).normalized();
    Ray lightRay(intersection.position, toLight);

    float participation = light->getParticipation(this->scene, lightRay);
    if(participation > Light::EPSILON) {
      // TODO: support attenuation with distance
      // TODO: support directed lights
      Color diffuse = object->getColor();
      Color specular(0, 0, 0);

      float cosPhi = (-ray->direction).dot(toLight);
      if(cosPhi > 0) {
        // ----- Reflection
        diffuse *= mat.diffuseReflection
                   * toLight.dot(intersection.normal);

        float cosAlpha = toLight.dot(symmetric);
        specular = mat.specularReflection * Color(1, 1, 1)
                    * pow(cosAlpha, mat.specularExponent);
      }
      else {
        // ----- Transmission
        // TODO: should this fix shadows through glass?
        // TODO: check for correctness
        diffuse *= mat.diffuseTransmission
                  * -toLight.dot(intersection.normal);

        // TODO: support specular transmission (depends on the refractive indices of the mediums)

      }

      lightColor += participation * (light->getColor().cwiseProduct(diffuse + specular));
    }
  }

  // ----- Ideal transmission (e.g. glass)
  Color transmissionColor(0, 0, 0);

  // TODO: support rays coming from a medium different than air
  float nn = (1 / mat.refractionIndex);
  float radical = (1 + nn*nn * (cosTheta * cosTheta - 1));

  if(radical > 0) {
    float tau = nn * cosTheta - sqrt(radical);
    Vec trans = nn * ray->direction
                + tau * intersection.normal;
    Ray transmissionRay(intersection.position, trans);

    float t = mat.idealTransmission;
    transmissionColor = t * castRay(transmissionRay, t * intensity);
  }
  // Otherwise, there's total reflection

  // ----- Ideal reflection (e.g. mirror)
  Ray reflectionRay(intersection.position, symmetric);
  float r = mat.idealReflection;
  Color reflectionColor = r * castRay(reflectionRay, r * intensity);

  return lightColor + transmissionColor + reflectionColor;
}
