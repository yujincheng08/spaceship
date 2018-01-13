#include "pointlight.h"

PointLight::PointLight(QNode *parent) : Light(parent) {
  light->setColor(QColor(255, 255, 255));
  light->setEnabled(true);
  addComponent(light);
}
