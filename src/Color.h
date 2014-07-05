#ifndef COLOR_H
#define COLOR_H

#include <Eigen/Core>
#include <time.h>

/** RGB colors, each component ranging from 0 to 1 */
typedef Eigen::Vector3f Color;
/** RGB colors, each component ranging from 0 to 255 */
typedef Eigen::Vector3i Pixel;

/**
 * Clip all components of the color to be within min and max
 */
inline Color clip(Color & c, float min = 0, float max = 1) {
  Color clipped = c;
  for(int i = 0; i < 3; ++i) {
    if(clipped[i] < min)
      clipped[i] = min;
    else if(clipped[i] > max)
      clipped[i] = max;
  }
  return clipped;
}

/**
 * @return A randomly generated color.
 * @TODO Use a better random generator
 */
inline Color getRandomColor() {
  srand(clock());
  return Color((float)rand(), (float)rand(), (float)rand());
}

/**
 * Turn a color into a displayable pixel
 */
inline Pixel colorToPixel(Color & c) {
  Color clipped = clip(c);
  return Pixel(
      (int)(clipped[0] * 255),
      (int)(clipped[1] * 255),
      (int)(clipped[2] * 255)
    );
}

#endif
