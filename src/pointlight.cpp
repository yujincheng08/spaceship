#include "pointlight.h"

PointLight::PointLight(QNode *parent) : Light(parent) {
  light->setColor(QColor(255, 0, 0));
  light->setEnabled(true);
  addComponent(light);
}
