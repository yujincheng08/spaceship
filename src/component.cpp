#include "component.h"
#include <QBitmap>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Component::Component(QNode *parent) : QEntity(parent) {
  addComponent(transform);
}

QVector3D Component::getPostion() const { return transform->translation(); }

void Component::setPosition(QVector3D translation) {
  transform->setTranslation(translation);
}

QVector3D Component::getToward() const {
  return (transform->rotation() * initDir.conjugated())
      .rotatedVector({0, 0, 1})
      .normalized();
}

QVector3D Component::getUp() const {
  return (transform->rotation() * initDir.conjugated())
      .rotatedVector({0, 1, 0})
      .normalized();
}

void Component::setInitialDirection(const QVector3D &toward,
                                    const QVector3D &up) {
  initDir = QQuaternion::fromDirection(toward, up).normalized();
  transform->setRotation(initDir);
}

void Component::setDirection(const QVector3D &toward, const QVector3D &up) {
  QQuaternion crtDir = (initDir * /*QQuaternion::rotationTo({0, 0, 1}, toward)*/
                        QQuaternion::fromDirection(toward, up).normalized())
                           .normalized();
  transform->setRotation(crtDir);
}
