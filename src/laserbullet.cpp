#include "laserbullet.h"
#include "scene.h"

LaserBullet::LaserBullet(const QVector3D &startPos, const QVector3D &velocity,
                         Scene *parent)
    : Component(parent) {

  this->root = root;

  this->velocity = velocity;
  length = velocity.length() / 5;
  setPosition(startPos + velocity.normalized() * length / 2);
  color = QColor(225, 75, 42);
  existTime = 0;

  mesh->setBottomRadius(0.14);
  mesh->setTopRadius(0.1);
  mesh->setLength(length);
  material->setShininess(1000000.0f);
  material->setAmbient(color);
  material->setDiffuse(color);
  material->setSpecular(color);
  material->setAlpha(0.2);

  transform->setRotation(QQuaternion::rotationTo({0, -1, 0}, velocity));

  addComponent(mesh);
  addComponent(material);
}

void LaserBullet::frameAction(float dt) {
  setPosition(getPostion() + velocity * dt);
  existTime += dt;
  if (existTime * velocity.length() > 200) {
    // root->removeLaserBullet(this);
  }
}
