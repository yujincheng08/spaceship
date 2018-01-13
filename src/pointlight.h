#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"
#include <Qt3DRender/QPointLight>

class PointLight : public Light {
public:
  using QPointLight = Qt3DRender::QPointLight;

public:
  void frameAction(float) {}
  PointLight(QNode *parent = nullptr);

private:
  QPointLight *light = new QPointLight;
};

#endif // POINTLIGHT_H
