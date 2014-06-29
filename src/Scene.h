#ifndef SCENE_H
#define SCENE_H

#include <string>

class Scene
{
public:
  Scene();
  virtual ~Scene();

  std::string getTitle();

protected:
  std::string title;
};

#endif
