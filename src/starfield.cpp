#include "starfield.h"
#include "scene.h"

Starfield::Starfield(Scene *parent) : Component(parent) {
  mesh->setSource(QUrl("qrc:/assets/starfield.obj"));
  textureImage->setSource(QUrl("qrc:/assets/img/galaxy_starfield.jpg"));
  texture->addTextureImage(textureImage);
  light->setRatio(parentScene()->width() / parentScene()->height());
  effect->setPlanetLight(light);
  material->setEffect(effect);
  material->setAmbient(QColor::fromRgbF(0, 0, 0));
  material->setSpecular(QColor::fromRgbF(0.0, 0.0, 0.0, 1.0));
  material->setDiffuseTexture("qrc:/assets/img/galaxy_starfield.jpg");
  material->setShiness(1000000.0f);
  // material->setSpecular(QColor::fromRgbF(0.0f, 0.0f, 0.0f, 1.0f));
  // material->setAmbient(QColor::fromRgb(0, 0, 0));
  // material->setDiffuse(texture);
  // material->setShininess(1000000.0);
  addComponent(mesh);
  addComponent(material);
  transform->setScale(850000);
  transform->setTranslation({0.0f, 0.0f, 0.0f});
}
