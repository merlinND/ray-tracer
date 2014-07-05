#ifndef COLOR_H
#define COLOR_H

#include <Eigen/Core>

typedef Eigen::Vector3f Color;

Color clip(Color c, float min = 0, float max = 1) {
  Color clipped = c;
  for(int i = 0; i < 3; ++i) {
    if(clipped[i] < min)
      clipped[i] = min;
    else if(clipped[i] > max)
      clipped[i] = max;
  }
  return clipped;
}

#endif
