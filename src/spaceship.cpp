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

void SpaceShip::setInitialDirection(const QVector3D &toward,
                                    const QVector3D &up) {
  initDir = QQuaternion::fromDirection(toward, up).normalized();
  transform->setRotation(initDir);
}

void SpaceShip::setDirection(const QVector3D &toward, const QVector3D &up) {
  QQuaternion crtDir = (initDir * /*QQuaternion::rotationTo({0, 0, 1}, toward)*/
                        QQuaternion::fromDirection(toward, up).normalized())
                           .normalized();
  transform->setRotation(crtDir);
}

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

  QVector3D chgTwd =
      (twd + up * turnUDSpeed * dt - left * turnLRSpeed * dt).normalized();
  QVector3D chgUp =
      (up - QVector3D::dotProduct(chgTwd, up) / chgTwd.length() * chgTwd)
          .normalized();

  setDirection({chgTwd.x(), -chgTwd.y(), chgTwd.z()},
               {-chgUp.x(), chgUp.y(), -chgUp.z()});

  setPosition(transform->translation() + chgTwd * moveSpeed * dt);
}
