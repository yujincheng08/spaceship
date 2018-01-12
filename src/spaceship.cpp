#include "spaceship.h"
#include <QtDebug>
#include <QtMath>

SpaceShip::SpaceShip(QNode *parent) : Component(parent) {
  mesh->setSource(QUrl("qrc:/assets/fj.obj"));
  textureImage->setSource(QUrl("qrc:/assets/img/earthmap2k.jpg"));
  texture->addTextureImage(textureImage);
  material->setTexture(texture);
  addComponent(mesh);
  addComponent(material);
  isTurnDown = isTurnLeft = isTurnRight = isTurnUp = false;
  isMoveForward = isMoveBack = false;
  setMaxMoveSpeed(1);
  setMaxTurnLRSpeed(1);
  setMaxTurnUDSpeed(1);
  turnLRSpeed = turnUDSpeed = moveSpeed = 0;
  //  qDebug() << "spaceship constructed.";
}

void SpaceShip::startTurnLeft() { isTurnLeft = true; }

void SpaceShip::startTurnRight() { isTurnRight = true; }

void SpaceShip::startTurnUp() { isTurnUp = true; }

void SpaceShip::startTurnDown() { isTurnDown = true; }

void SpaceShip::startMoveForward() { isMoveForward = true; }

void SpaceShip::startMoveBack() { isMoveBack = true; }

void SpaceShip::endTurnLeft() { isTurnLeft = false; }

void SpaceShip::endTurnRight() { isTurnRight = false; }

void SpaceShip::endTurnUp() { isTurnUp = false; }

void SpaceShip::endTurnDown() { isTurnDown = false; }

void SpaceShip::endMoveForward() { isMoveForward = false; }

void SpaceShip::endMoveBack() { isMoveBack = false; }

QVector3D SpaceShip::getToward() {
  return (transform->rotation() * initDir.conjugated())
      .rotatedVector({0, 0, 1})
      .normalized();
}

QVector3D SpaceShip::getUp() {
  return (transform->rotation() * initDir.conjugated())
      .rotatedVector({0, 1, 0})
      .normalized();
}

void SpaceShip::frameAction(float dt) {
  if (isTurnLeft && !isTurnRight)
    if (turnLRSpeed > -maxTurnLRSpeed)
      turnLRSpeed -= maxTurnLRSpeed / 25;
  if (isTurnRight && !isTurnLeft)
    if (turnLRSpeed < maxTurnLRSpeed)
      turnLRSpeed += maxTurnUDSpeed / 25;
  if (isTurnUp && !isTurnDown)
    if (turnUDSpeed < maxTurnUDSpeed)
      turnUDSpeed += maxTurnUDSpeed / 50;
  if (isTurnDown && !isTurnUp)
    if (turnUDSpeed > -maxTurnUDSpeed)
      turnUDSpeed -= maxTurnUDSpeed / 50;
  if (isMoveForward && !isMoveBack)
    if (moveSpeed < maxMoveSpeed)
      moveSpeed += maxMoveSpeed / 25;
  if (isMoveBack && !isMoveForward)
    if (moveSpeed > -maxMoveSpeed)
      moveSpeed -= maxMoveSpeed / 25;

  QVector3D twd = getToward();
  QVector3D up = getUp();
  QVector3D left = QVector3D::crossProduct(up, twd).normalized();

  //  qDebug() << "td" << twd.x() << twd.y() << twd.z();
  //  qDebug() << "up" << up.x() << up.y() << up.z();
  //  qDebug() << "lf" << left.x() << left.y() << left.z();

  QVector3D chgTwd = twd - up * turnUDSpeed * dt - left * turnLRSpeed * dt;

  QQuaternion orgQQtn = transform->rotation(),
              chgQQtn = QQuaternion::rotationTo(twd, chgTwd);

  //  qDebug() << "org" << orgQQtn.x() << orgQQtn.y() << orgQQtn.z();
  //  qDebug() << "chg" << chgQQtn.x() << chgQQtn.y() << chgQQtn.z();

  //  qDebug() << "cup" << chgUp.x() << chgUp.y() << chgUp.z();
  //  qDebug() << "clf" << chgLeft.x() << chgLeft.y() << chgLeft.z();

  //  qDebug() << "org" << twd.x() << twd.y() << twd.z();
  //  qDebug() << "chg" << chgTwd.x() << chgTwd.y() << chgTwd.z();

  transform->setRotation((orgQQtn * chgQQtn).normalized());
}

// void SpaceShip::spaceshipRotate() {
//  QVector3D orgT{originTX, originTY, originTZ};
//  QVector3D T{towardX, towardY, towardZ};

//  QVector3D axis = QVector3D::crossProduct(orgT, T);
//  T.normalize();
//  orgT.normalize();
//  GLdouble ang = qAcos(QVector3D::dotProduct(T, orgT));
//  if (ang < 0)
//    ang = ang + M_PI + M_PI;
//  glRotated(ang / M_PI * 180, axis.x(), axis.y(), axis.z());
//}
