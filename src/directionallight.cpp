#include "directionallight.h"

DirectionalLight::DirectionalLight(Scene *parent) : Light(parent) {
  light->setWorldDirection({0, -1, 0});
  addComponent(light);
}
