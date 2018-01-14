#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "component.h"
#include <QSceneChange>
#include <QtOpenGL>

class Scene;

class SpaceShip : public Component {
  using QPhongAlphaMaterial = Qt3DExtras::QPhongAlphaMaterial;

public:
  QSceneLoader *sceneLoader = new QSceneLoader;

  QTextureMaterial *material = new QTextureMaterial;
  QTextureImage *textureImage = new QTextureImage;
  QTexture2D *texture = new QTexture2D;

  friend class InfoSurface;
  SpaceShip(QNode *parent = nullptr, Scene *root = nullptr);

  void startTurnLeft() { isTurnLeft = true; }
  void startTurnRight() { isTurnRight = true; }
  void startTurnUp() { isTurnUp = true; }
  void startTurnDown() { isTurnDown = true; }
  void startMoveForward() { isMoveForward = true; }
  void startMoveBack() { isMoveBack = true; }
  void startShoot() { isShooting = true; }
  void endTurnLeft() { isTurnLeft = false; }
  void endTurnRight() { isTurnRight = false; }
  void endTurnUp() { isTurnUp = false; }
  void endTurnDown() { isTurnDown = false; }
  void endMoveForward() { isMoveForward = false; }
  void endMoveBack() { isMoveBack = false; }
  void endShoot() {
    isShooting = false;
    shootWait = 0;
  }
  void setMaxTurnLRSpeed(qreal speed) { maxTurnLRSpeed = speed; }
  void setMaxTurnUDSpeed(qreal speed) { maxTurnUDSpeed = speed; }
  void setMaxMoveSpeed(qreal speed) { maxMoveSpeed = speed; }
  void setInitialDirection(const QVector3D &toward, const QVector3D &up);
  void setDirection(const QVector3D &toward, const QVector3D &up);

  QVector3D getToward() const;
  QVector3D getUp() const;
  virtual ~SpaceShip() {}

protected slots:
  virtual void frameAction(float dt) override;

private:
  qreal turnLRSpeed, turnUDSpeed, moveSpeed, shootWait;
  qreal maxTurnLRSpeed, maxTurnUDSpeed, maxMoveSpeed, shootInterval;
  QMap<QString, QMaterial *> materials;
  QQuaternion initDir;

  bool isTurnLeft, isTurnRight, isTurnUp, isTurnDown, isMoveForward, isMoveBack,
      isShooting;
  QPhongMaterial *bodyMaterial = new QPhongMaterial;
  /*
  QPhongMaterial *feetMaterial = new QPhongMaterial;
  QPhongMaterial *gamaMaterial = new QPhongMaterial;
  QPhongMaterial *reactorMaterial = new QPhongMaterial;
  QPhongMaterial *wingMaterial = new QPhongMaterial;
  */
  QPhongAlphaMaterial *glassMaterial = new QPhongAlphaMaterial;
  QPhongAlphaMaterial *gasMaterial = new QPhongAlphaMaterial;

  Scene *root;

private:
  void removeDefaultMaterial(const QString &entityName);
  void initMaterials();
private slots:
  void loadingStatusChanged(QSceneLoader::Status status);
};

#endif // SPACESHIP_H
