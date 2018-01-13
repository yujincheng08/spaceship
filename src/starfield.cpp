#include "starfield.h"

Starfield::Starfield(QNode *parent) : Component(parent) {
  mesh->setSource(QUrl("qrc:/assets/starfield.obj"));
  textureImage->setSource(QUrl("qrc:/assets/img/galaxy_starfield.jpg"));
  texture->addTextureImage(textureImage);
  material->setSpecular(QColor::fromRgbF(0.0f, 0.0f, 0.0f, 1.0f));
  material->setAmbient(QColor::fromRgb(0, 0, 0));
  material->setDiffuse(texture);
  material->setShininess(1000000.0);
  addComponent(mesh);
  addComponent(material);
  transform->setScale(850000);
  transform->setTranslation({0.0f, 0.0f, 0.0f});
}
