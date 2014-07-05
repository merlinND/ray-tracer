#include "Light.h"

Light::Light(Color const & c)
  : color(c) {

}

void Light::setColor(Color const & c) {
  this->color = c;
}
