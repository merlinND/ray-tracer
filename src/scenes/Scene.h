#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "../renderer/Color.h"
#include "../lights/AmbientLight.h"
#include "../lights/PunctualLight.h"
#include "../geometry/Object.h"

class Scene {
public:
  std::string title;
  Color background;
  AmbientLight ambientLight;
  std::vector<PunctualLight *> lightSources;
  std::vector<Object *> objects;

  Scene(Color const & bg, std::string title);
  virtual ~Scene();

  void addObject(Object * object);
  void addLightSource(PunctualLight * light);

  /**
   * Compute an intersection of the ray with the objects
   * from the scene.
   * @param ray The ray to test
   * @param intersection Output object for intersection data. Pass NULL if you don't need this data.
   * @return Whether or not there's any intersection
   */
  bool intersects(Ray const & ray, Intersection * intersection) const;

protected:
};

#endif
