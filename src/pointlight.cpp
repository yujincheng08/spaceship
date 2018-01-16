#include "pointlight.h"

PointLight::PointLight(Scene *parent) : Light(parent) {
  light->setColor(QColor(255, 255, 255));
  light->setEnabled(true);
  addComponent(light);
}
