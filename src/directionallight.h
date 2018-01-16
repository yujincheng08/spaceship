#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "light.h"
#include <Qt3DRender/QDirectionalLight>

class DirectionalLight : public Light {
public:
  using QDirectionalLight = Qt3DRender::QDirectionalLight;

public:
  DirectionalLight(Scene *parent = nullptr);

private:
  QDirectionalLight *light = new QDirectionalLight;
};

#endif // DIRECTIONALLIGHT_H
