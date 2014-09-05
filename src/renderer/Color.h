#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <Eigen/Core>
#include "../util/mersenneTwister.h"

/** RGB colors, each component ranging from 0 to 255 */
typedef Eigen::Matrix<uint8_t, 3, 1> Pixel;
/** RGB colors, each component ranging from 0 to 1 */
typedef Eigen::Vector3f Color;

namespace Colors {
  static Color const BLACK = Color(0, 0, 0),
                     WHITE = Color(1, 1, 1),
                     DARK_GREY = Color(0.25, 0.25, 0.25),
                     GREY = Color(0.5, 0.5, 0.5),
                     LIGHT_GREY = Color(0.75, 0.75, 0.75),
                     RED = Color(1, 0, 0),
                     GREEN = Color(0, 1, 0),
                     BLUE = Color(0, 0, 1),
                     PURPLE = Color(1, 0, 1);

};


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

inline Color colorFromRGB(uint8_t r, uint8_t g, uint8_t b) {
  return Color(
      (float)(r / 255.0),
      (float)(g / 255.0),
      (float)(b / 255.0)
    );
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
