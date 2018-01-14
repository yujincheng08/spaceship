#include "spaceship.h"
#include "scene.h"
#include <QtDebug>
#include <QtMath>

SpaceShip::SpaceShip(QNode *parent, Scene *root) : Component(parent) {
  this->root = root;
  initMaterials();
  textureImage->setSource(QUrl("qrc:/assets/img/earthmap2k.jpg"));
  texture->addTextureImage(textureImage);
  material->setTexture(texture);
  addComponent(sceneLoader);
  connect(sceneLoader, &QSceneLoader::statusChanged, this,
          &SpaceShip::loadingStatusChanged);
  sceneLoader->setSource(QUrl("qrc:/assets/spaceship.obj"));
  // addComponent(material);
  isTurnDown = isTurnLeft = isTurnRight = isTurnUp = false;
  isMoveForward = isMoveBack = false;
  setMaxMoveSpeed(5);
  setMaxTurnLRSpeed(1);
  setMaxTurnUDSpeed(1);
  turnLRSpeed = turnUDSpeed = moveSpeed = 0;

  shootWait = 0;
  shootInterval = 0.5;
  //  qDebug() << "spaceship constructed.";
}

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

QVector3D SpaceShip::getToward() const {
  return (transform->rotation() * initDir.conjugated())
      .rotatedVector({0, 0, 1})
      .normalized();
}

QVector3D SpaceShip::getUp() const {
  return (transform->rotation() * initDir.conjugated())
      .rotatedVector({0, 1, 0})
      .normalized();
}

void SpaceShip::frameAction(float dt) {
  // move
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

  // shoot
  if (!isShooting)
    return;
  shootWait += dt;
  if (shootWait < shootInterval)
    return;
  shootWait -= shootInterval;
  root->addLaserBullet(this->getPostion(), 100);
}

void SpaceShip::removeDefaultMaterial(const QString &entityName) {
  auto entity = sceneLoader->entity(entityName);
  auto material =
      sceneLoader->component(entityName, QSceneLoader::MaterialComponent);
  entity->removeComponent(material);
}

void SpaceShip::initMaterials() {
  materials["Body"] = bodyMaterial;
  materials["Wings"] = bodyMaterial;
  materials["Feet"] = bodyMaterial;
  materials["Gama"] = bodyMaterial;
  materials["Reactor"] = bodyMaterial;
  materials["Glass"] = glassMaterial;
  materials["Gas"] = gasMaterial;
  bodyMaterial->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  bodyMaterial->setDiffuse(QColor::fromRgbF(0.8f, 0.8f, 0.8f));
  bodyMaterial->setSpecular(QColor::fromRgbF(0.5f, 0.5f, 0.5f));
  gasMaterial->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  gasMaterial->setDiffuse(QColor::fromRgbF(0.8f, 0.8f, 0.8f));
  gasMaterial->setSpecular(QColor::fromRgbF(0.5f, 0.5f, 0.5f));
  gasMaterial->setAlpha(0.0f);
  glassMaterial->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  glassMaterial->setDiffuse(QColor::fromRgbF(0.8f, 0.8f, 0.8f));
  glassMaterial->setSpecular(QColor::fromRgbF(0.5f, 0.5f, 0.5f));
  glassMaterial->setAlpha(0.3f);
}

void SpaceShip::loadingStatusChanged(Qt3DRender::QSceneLoader::Status status) {
  switch (status) {
  case QSceneLoader::Ready:
    for (const auto &entity : sceneLoader->entityNames()) {
      removeDefaultMaterial(entity);
      sceneLoader->entity(entity)->addComponent(materials[entity]);
    }
    break;
  case QSceneLoader::Error:
    qDebug() << "Error";
  }
}
