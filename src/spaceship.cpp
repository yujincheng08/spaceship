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
  isTurnDown = isTurnLeft = isTurnRight = isTurnUp = false;
  isMoveForward = isMoveBack = false;
  isExploded = false;
  setMaxMoveSpeed(5);
  setMaxTurnLRSpeed(1);
  setMaxTurnUDSpeed(1);
  turnLRSpeed = turnUDSpeed = moveSpeed = 0;

  shootWait = 0;
  shootInterval = 0.5;
}

void SpaceShip::explode() {
  explodeList = new QList<QTransform *>;
  for (const auto &entity : sceneLoader->entityNames())
    if (((QString)entity)[2] != 's') {
      QTransform *transform = new QTransform[2];
      explodeList->append(transform);
      transform[0].setTranslation(
          QVector3D(noise(-1, 1), noise(-1, 1), noise(-1, 1)).normalized() *
          noise(1, 3));
      transform[0].setRotationX(noise(0, 1));
      transform[0].setRotationY(noise(0, 1));
      transform[0].setRotationZ(noise(0, 1));
      transform[1].setTranslation(transform[0].translation());
      transform[1].setRotation(transform[0].rotation());
      sceneLoader->entity(entity)->addComponent(transform);
    }
  gasTransUL->setScale(0);
  gasTransUM->setScale(0);
  gasTransUR->setScale(0);
  gasTransDL->setScale(0);
  gasTransDR->setScale(0);
  isExploded = true;
  explodeTime = 0;
}

void SpaceShip::frameAction(float dt) {
  if (isExploded) {
    if (explodeList == nullptr)
      return;
    for (QTransform *trans : *explodeList) {
      trans[0].setTranslation(trans[0].translation() +
                              trans[1].translation() * dt);
      trans[0].setRotationX(trans[0].rotationX() + trans[1].rotationX());
      trans[0].setRotationY(trans[0].rotationY() + trans[1].rotationY());
      trans[0].setRotationZ(trans[0].rotationZ() + trans[1].rotationZ());
    }
    explodeTime += dt;
    if (explodeTime > 10)
      root->spaceshipExplode(this);
  } else {
    int direct;
    // move
    if (isMoveForward && !isMoveBack) {
      direct = 1;
      if (moveSpeed < maxMoveSpeed)
        moveSpeed += maxMoveSpeed / 25;
    } else if (isMoveBack && !isMoveForward) {
      direct = -1;
      if (moveSpeed > -maxMoveSpeed)
        moveSpeed -= maxMoveSpeed / 25;
    } else
      direct = 0;
    direct *= 3;
    if (isTurnLeft && !isTurnRight) {
      direct += 1;
      if (turnLRSpeed > -maxTurnLRSpeed)
        turnLRSpeed -= maxTurnLRSpeed / 25;
    } else if (isTurnRight && !isTurnLeft) {
      direct -= 1;
      if (turnLRSpeed < maxTurnLRSpeed)
        turnLRSpeed += maxTurnUDSpeed / 25;
    }
    direct *= 3;
    if (isTurnUp && !isTurnDown) {
      direct += 1;
      if (turnUDSpeed < maxTurnUDSpeed)
        turnUDSpeed += maxTurnUDSpeed / 50;
    } else if (isTurnDown && !isTurnUp) {
      direct -= 1;
      if (turnUDSpeed > -maxTurnUDSpeed)
        turnUDSpeed -= maxTurnUDSpeed / 50;
    }

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

    // tail fire
    checkTailFire(direct);

    // shoot
    if (!isShooting)
      return;
    shootWait += dt;
    if (shootWait < shootInterval)
      return;
    shootWait -= shootInterval;
    root->addLaserBullet(this->getPostion(), 100);
  }
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
  materials["Glass"] = glassMaterial;
  materials["GasUL"] = gasMaterialUL;
  materials["GasUM"] = gasMaterialUM;
  materials["GasUR"] = gasMaterialUR;
  materials["GasDL"] = gasMaterialDL;
  materials["GasDR"] = gasMaterialDR;
  // bodyMaterial->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  bodyMaterial->setAmbient(QColor::fromRgbF(0.2f, 0.2f, 0.2f));
  bodyMaterial->setDiffuse(QColor::fromRgbF(0.8f, 0.8f, 0.8f));
  bodyMaterial->setSpecular(QColor::fromRgbF(0.5f, 0.5f, 0.5f));
  gasMaterialUL->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  gasMaterialUL->setDiffuse(QColor::fromRgbF(0.0f, 0.0f, 0.8f));
  gasMaterialUL->setSpecular(QColor::fromRgbF(0.0f, 0.0, 0.0f));
  gasMaterialUL->setAlpha(0.2f);
  gasMaterialUM->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  gasMaterialUM->setDiffuse(QColor::fromRgbF(0.0f, 0.0f, 0.8f));
  gasMaterialUM->setSpecular(QColor::fromRgbF(0.0f, 0.0, 0.0f));
  gasMaterialUM->setAlpha(0.2f);
  gasMaterialUR->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  gasMaterialUR->setDiffuse(QColor::fromRgbF(0.0f, 0.0f, 0.8f));
  gasMaterialUR->setSpecular(QColor::fromRgbF(0.0f, 0.0, 0.0f));
  gasMaterialUR->setAlpha(0.2f);
  gasMaterialDL->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  gasMaterialDL->setDiffuse(QColor::fromRgbF(0.0f, 0.0f, 0.8f));
  gasMaterialDL->setSpecular(QColor::fromRgbF(0.0f, 0.0, 0.0f));
  gasMaterialDL->setAlpha(0.2f);
  gasMaterialDR->setAmbient(QColor::fromRgbF(1.0f, 1.0f, 1.0f));
  gasMaterialDR->setDiffuse(QColor::fromRgbF(0.0f, 0.0f, 0.8f));
  gasMaterialDR->setSpecular(QColor::fromRgbF(0.0f, 0.0, 0.0f));
  gasMaterialDR->setAlpha(0.2f);
  glassMaterial->setAmbient(QColor::fromRgbF(0.0f, 0.0f, 0.0f));
  glassMaterial->setDiffuse(QColor::fromRgbF(0.0f, 0.0f, 0.0f));
  glassMaterial->setSpecular(QColor::fromRgbF(0.8f, 0.8f, 0.8f));
}

void SpaceShip::loadingStatusChanged(Qt3DRender::QSceneLoader::Status status) {
  switch (status) {
  case QSceneLoader::Ready:
    for (const auto &entity : sceneLoader->entityNames()) {
      removeDefaultMaterial(entity);
      sceneLoader->entity(entity)->addComponent(materials[entity]);
      if (((QString)entity) == "GasUL")
        sceneLoader->entity(entity)->addComponent(gasTransUL);
      else if (((QString)entity) == "GasUM")
        sceneLoader->entity(entity)->addComponent(gasTransUM);
      else if (((QString)entity) == "GasUR")
        sceneLoader->entity(entity)->addComponent(gasTransUR);
      else if (((QString)entity) == "GasDL")
        sceneLoader->entity(entity)->addComponent(gasTransDL);
      else if (((QString)entity) == "GasDR")
        sceneLoader->entity(entity)->addComponent(gasTransDR);
    }
    break;
  case QSceneLoader::Error:
    qDebug() << "Error";
  case QSceneLoader::Loading:
    qDebug() << "Still loading...";
    break;
  default:
    break;
  }
}

void SpaceShip::checkTailFire(const int &direct) {
  float ull, uml, url, dll, drl;
  bool ulc, umc, urc, dlc, drc;
  float l1 = 0.6, l2 = 0.8, l3 = 0.9, l4 = 1;
  if (direct < -4)
    ulc = umc = urc = dlc = drc = false;
  else if (direct > 4)
    ulc = umc = urc = dlc = drc = true;
  else
    ull = uml = url = dll = drl = l3;
  switch (direct) {
  case -13: // back right down
    ull = l1;
    uml = l2;
    url = l3;
    dll = l3;
    drl = l4;
    break;
  case -12: // back right keep
    ull = l2;
    uml = l3;
    url = l4;
    dll = l2;
    drl = l4;
    break;
  case -11: // back right up
    ull = l2;
    uml = l3;
    url = l4;
    dll = l2;
    drl = l3;
    break;
  case -10: // back keep down
    ull = l2;
    uml = l3;
    url = l2;
    dll = l4;
    drl = l4;
    break;
  case -9: // back keep keep
    ull = l3;
    uml = l3;
    url = l3;
    dll = l3;
    drl = l3;
    break;
  case -8: // back keep up
    ull = l4;
    uml = l4;
    url = l4;
    dll = l2;
    drl = l2;
    break;
  case -7: // back left down
    ull = l3;
    uml = l2;
    url = l1;
    dll = l4;
    drl = l3;
    break;
  case -6: // back left keep
    ull = l4;
    uml = l3;
    url = l2;
    dll = l4;
    drl = l2;
    break;
  case -5: // back left up
    ull = l4;
    uml = l3;
    url = l2;
    dll = l3;
    drl = l2;
    break;
  case -4: // keep right down
    ulc = true;
    umc = true;
    urc = false;
    dlc = true;
    drc = false;
    break;
  case -3: // keep right keep
    uml = l1;
    ulc = true;
    umc = true;
    urc = false;
    dlc = true;
    drc = false;
    break;
  case -2: // keep right up
    ulc = true;
    umc = false;
    urc = false;
    dlc = true;
    drc = false;
    break;
  case -1: // keep keep down
    ulc = umc = urc = true;
    dlc = drc = false;
    break;
  case 0: // keep keep keep
    ull = uml = url = dll = drl = l1;
    ulc = umc = urc = dlc = drc = true;
    break;
  case 1: // keep keep up
    ulc = umc = urc = false;
    dlc = drc = true;
    break;
  case 2: // keep left down
    ulc = false;
    umc = true;
    urc = true;
    dlc = false;
    drc = true;
    break;
  case 3: // keep left keep
    uml = l1;
    ulc = false;
    umc = true;
    urc = true;
    dlc = false;
    drc = true;
    break;
  case 4: // keep left up
    ulc = false;
    umc = false;
    urc = true;
    dlc = false;
    drc = true;
    break;
  case 5: // forward right down
    ull = l4;
    uml = l3;
    url = l2;
    dll = l3;
    drl = l2;
    break;
  case 6: // forward right keep
    ull = l4;
    uml = l3;
    url = l2;
    dll = l4;
    drl = l2;
    break;
  case 7: // forward right up
    ull = l3;
    uml = l2;
    url = l1;
    dll = l4;
    drl = l3;
    break;
  case 8: // forward keep down
    ull = l4;
    uml = l4;
    url = l4;
    dll = l2;
    drl = l2;
    break;
  case 9: // forward keep keep
    ull = l3;
    uml = l3;
    url = l3;
    dll = l3;
    drl = l3;
    break;
  case 10: // forward keep up
    ull = l2;
    uml = l3;
    url = l2;
    dll = l4;
    drl = l4;
    break;
  case 11: // forward left down
    ull = l2;
    uml = l3;
    url = l4;
    dll = l2;
    drl = l3;
    break;
  case 12: // forward left keep
    ull = l2;
    uml = l3;
    url = l4;
    dll = l2;
    drl = l4;
    break;
  case 13: // forward left up
    ull = l1;
    uml = l2;
    url = l3;
    dll = l3;
    drl = l4;
    break;
  }
  gasTransUL->setScale3D({1, 1, noise(ull)});
  gasTransUM->setScale3D({1, 1, noise(uml)});
  gasTransUR->setScale3D({1, 1, noise(url)});
  gasTransDL->setScale3D({1, 1, noise(dll)});
  gasTransDR->setScale3D({1, 1, noise(drl)});
  gasMaterialUL->setDiffuse(QColor::fromRgbF(
      noise(ulc ? 0.8f : 0.1f), noise(0.1f), noise(ulc ? 0.1f : 0.8f)));
  gasMaterialUM->setDiffuse(QColor::fromRgbF(
      noise(umc ? 0.8f : 0.1f), noise(0.1f), noise(umc ? 0.1f : 0.8f)));
  gasMaterialUR->setDiffuse(QColor::fromRgbF(
      noise(urc ? 0.8f : 0.1f), noise(0.1f), noise(urc ? 0.1f : 0.8f)));
  gasMaterialDL->setDiffuse(QColor::fromRgbF(
      noise(dlc ? 0.8f : 0.1f), noise(0.1f), noise(dlc ? 0.1f : 0.8f)));
  gasMaterialDR->setDiffuse(QColor::fromRgbF(
      noise(drc ? 0.8f : 0.1f), noise(0.1f), noise(drc ? 0.1f : 0.8f)));
  gasMaterialUL->setAlpha(noise(0.3f));
  gasMaterialUM->setAlpha(noise(0.4f));
  gasMaterialUR->setAlpha(noise(0.3f));
  gasMaterialDL->setAlpha(noise(0.3f));
  gasMaterialDR->setAlpha(noise(0.3f));
}

float SpaceShip::noise(const float &orgFLT) {
  float noi = (qrand() % 1001) / 10000.0 - 0.05;
  noi += orgFLT;
  if (noi < 0)
    return 0;
  if (noi > 1)
    return 1;
  return noi;
}

float SpaceShip::noise(const float &low, const float &high) {
  float noi = (qrand() % 1001) / 1000.0;
  return low + noi * (high - low);
}
