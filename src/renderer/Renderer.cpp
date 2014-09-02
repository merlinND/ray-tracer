#include <iostream>
#include <vector>
using namespace std;

#include "../geometry/Object.h"
#include "../geometry/Intersection.h"
#include "../lights/PunctualLight.h"

#include "Renderer.h"

// TODO: tweak values
float const Renderer::MIN_INTENSITY = 0.05;
uint const Renderer::OVERSAMPLING_PERIOD = 2;
uint const Renderer::OVERSAMPLING_PERIOD2 = Renderer::OVERSAMPLING_PERIOD * Renderer::OVERSAMPLING_PERIOD;
// Good range for this threshold: between 0.01 and 0.0001
float const Renderer::OVERSAMPLING_THRESHOLD = 0.005;

Renderer::Renderer(Scene & s, Camera & c)
  : scene(s), camera(c) {
}

bool Renderer::shouldOversample(Image const & image, int x, int y) {
  Color primary = image.get(x, y);
  Color difference;
  vector<Color *> neighbors = image.getNeighbors(x, y);
  for(uint i = 0; i < neighbors.size(); ++i) {
    difference = *(neighbors[i]) - primary;
    if(difference.squaredNorm() > Renderer::OVERSAMPLING_THRESHOLD) {
      return true;
    }
  }

  return false;
}

void Renderer::render(Image & image) {
  float progress = 0;
  cout << endl << "Casting primary rays" << flush;

  // Ofset from the corner of a pixel to its center (in meters)
  float ox = (1 / (float)image.width) / 2,
        oy = (1 / (float)image.height) / 2;

  for(int x = 0; x < image.width; ++x) {
    for(int y = 0; y < image.height; ++y) {
      // We cast from the center of the pixel, not its corner
      float ix = (x / (float)image.width) + ox,
            iy = (y / (float)image.height) + oy;
      Ray r = this->camera.getRay(ix, iy);
      image.set(x, y, castRay(r, 1));
    }

    float currentProgress = (x / (float)image.width);
    if(currentProgress >= progress + 0.05) {
      cout << "." << flush;
      progress = currentProgress;
    }
  }
  cout << ".done" << endl;

  oversamplingPass(image);
}

void Renderer::oversamplingPass(Image & image) {
  uint oversamplingCount = 0;
  cout << "Oversampling pass..." << flush;

  // Stride when oversampling around a pixel
  float dx = (1 / (float)image.width) / (float)Renderer::OVERSAMPLING_PERIOD,
        dy = (1 / (float)image.height) / (float)Renderer::OVERSAMPLING_PERIOD;
  int middle = (Renderer::OVERSAMPLING_PERIOD / 2);

  Color accumulator;
  for(int x = 0; x < image.width; ++x) {
    for(int y = 0; y < image.height; ++y) {
      float ix = (x / (float)image.width),
            iy = (y / (float)image.height);
      // If any of its neighbors is too different from this pixel,
      // trigger oversampling
      if(shouldOversample(image, x, y)) {
        oversamplingCount++;

        // This color corresponds to the center of the pixel
        // (as computed during the first pass)
        accumulator = image.get(x, y);

        for(int i = 0; i < Renderer::OVERSAMPLING_PERIOD; ++i) {
          for(int j = 0; j < Renderer::OVERSAMPLING_PERIOD; ++j) {
            // No need to recast the center ray
            if(i != middle || j != middle) {
              Ray r = this->camera.getRay(ix + i * dx, iy + j * dy);
              accumulator += castRay(r, 1);
            }
          }
        }
        image.set(x, y, accumulator / Renderer::OVERSAMPLING_PERIOD2);
      }
    }
  }

  cout << " oversampled " << oversamplingCount << " pixels" << endl;
}

Color Renderer::castRay(Ray const & ray, float intensity) const {
  if(intensity < Renderer::MIN_INTENSITY) {
    return Colors::BLACK;
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
   * according to Descartes' laws.
   */
  Vec symmetric = (2 * cosTheta * intersection.normal) + ray->direction;

  /**
   * Determine the ideal direction of transmission
   * based on the position of the viewer.
   */
  bool totalReflection = true;
  Vec transmissionDirection;
  float nn = (ray->refractionIndex / mat.refractionIndex);
  float radical = (1 + nn*nn * (cosTheta * cosTheta - 1));
  if(radical > 0) {
    totalReflection = false;

    float tau = nn * cosTheta - sqrt(radical);
    transmissionDirection = nn * ray->direction
                + tau * intersection.normal;
  }

  // ----- Ambient light
  Color lightColor = mat.ambientLight
                    * this->scene.ambientLight.getColor()
                      .cwiseProduct(object->getColor(intersection));

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
      Color diffuse = object->getColor(intersection);
      Color specular(0, 0, 0);

      float cosPhi = (-ray->direction).dot(toLight);
      if(cosPhi > 0) {
        // ----- Reflection
        diffuse *= mat.diffuseReflection
                   * toLight.dot(intersection.normal);

        float cosAlpha = toLight.dot(symmetric);
        specular = mat.specularReflection * Colors::WHITE
                    * pow(cosAlpha, mat.specularExponent);
      }
      else {
        // ----- Transmission
        // Diffuse transmission
        // TODO: check for correctness
        diffuse *= mat.diffuseTransmission
                  * -toLight.dot(intersection.normal);

        // Specular transmission
        if(!totalReflection) {
          float cosAlpha = toLight.dot(transmissionDirection);
          if(cosAlpha > 0) {
            specular = mat.specularTransmission * Colors::WHITE
                       * pow(cosAlpha, mat.specularTransmissionExponent);
          }
        }
      }

      lightColor += participation * (light->getColor().cwiseProduct(diffuse + specular));
    }
  }

  // ----- Ideal transmission (e.g. glass)
  Color transmissionColor(0, 0, 0);

  if(!totalReflection) {
    Ray transmissionRay(intersection.position, transmissionDirection, mat.refractionIndex);
    // Push the transmission ray to the other side of the medium's frontier
    // so that it doesn't get stuck inside
    transmissionRay.from = transmissionRay.from - (2 * Object::PUSH_BACK * intersection.normal);

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
