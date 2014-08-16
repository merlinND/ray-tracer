#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <Eigen/Core>
#include "../util/mersenneTwister.h"

/** RGB colors, each component ranging from 0 to 1 */
typedef Eigen::Vector3f Color;
/** RGB colors, each component ranging from 0 to 255 */
typedef Eigen::Matrix<uint8_t, 3, 1> Pixel;

// TODO: make available an enum of often used colors

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
 */
inline Color getRandomColor() {
  return Color(mt_random(), mt_random(), mt_random());
}

/**
 * Turn a color into a displayable pixel
 */
inline Pixel colorToPixel(Color & c) {
  Color clipped = clip(c);
  return Pixel(
      (uint8_t)(clipped[0] * 255),
      (uint8_t)(clipped[1] * 255),
      (uint8_t)(clipped[2] * 255)
    );
}

/**
 * Pretty printing of colors
 */
inline std::ostream& operator<<(std::ostream& os, Color const & c) {
  os << "(" << c[0] << "," << c[1] << "," << c[2] << ")";
  return os;
}

#endif
