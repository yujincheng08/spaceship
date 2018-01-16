#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "component.h"
#include <QSceneChange>
#include <QTime>
#include <QtOpenGL>

class Controller;

class SpaceShip : public Component {
  using QPhongAlphaMaterial = Qt3DExtras::QPhongAlphaMaterial;

public:
  QSceneLoader *sceneLoader = new QSceneLoader;

  QTextureMaterial *material = new QTextureMaterial;
  QTextureImage *textureImage = new QTextureImage;
  QTexture2D *texture = new QTexture2D;

  friend class InfoSurface;
  SpaceShip(Scene *parent = nullptr, Controller *root = nullptr);
  QList<BoundingBox> boundingBoxes;

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
  bool isExplode() { return isExploded; }
  void explode() override;

  virtual QList<BoundingBox> getBoundingBox() const override {
    QList<BoundingBox> transformedBoundingBoxes;
    for (const auto &boundingBox : boundingBoxes)
      transformedBoundingBoxes << boundingBox.applyTransform(*transform);
    return transformedBoundingBoxes;
  }

  virtual QList<BoundingSphere> getBoundingSphere() const override {
    return QList<BoundingSphere>();
  }

  virtual ~SpaceShip() { removeComponent(sceneLoader); }

signals:
  void triggerBullet(QVector3D pos, QVector3D velocity);
  void triggerBullet(QVector3D pos, float speed);

protected slots:
  virtual void frameAction(float dt) override;

private:
  qreal turnLRSpeed, turnUDSpeed, moveSpeed, shootWait;
  qreal maxTurnLRSpeed, maxTurnUDSpeed, maxMoveSpeed, shootInterval;
  QMap<QString, QMaterial *> materials;

  bool isTurnLeft, isTurnRight, isTurnUp, isTurnDown, isMoveForward, isMoveBack,
      isShooting;
  bool isExploded;
  QPhongMaterial *bodyMaterial = new QPhongMaterial;
  /*
  QPhongMaterial *feetMaterial = new QPhongMaterial;
  QPhongMaterial *gamaMaterial = new QPhongMaterial;
  QPhongMaterial *reactorMaterial = new QPhongMaterial;
  QPhongMaterial *wingMaterial = new QPhongMaterial;
  */
  QPhongMaterial *glassMaterial = new QPhongMaterial;
  QPhongAlphaMaterial *gasMaterialUL = new QPhongAlphaMaterial;
  QPhongAlphaMaterial *gasMaterialUM = new QPhongAlphaMaterial;
  QPhongAlphaMaterial *gasMaterialUR = new QPhongAlphaMaterial;
  QPhongAlphaMaterial *gasMaterialDL = new QPhongAlphaMaterial;
  QPhongAlphaMaterial *gasMaterialDR = new QPhongAlphaMaterial;

  QTransform *gasTransUL = new QTransform;
  QTransform *gasTransUM = new QTransform;
  QTransform *gasTransUR = new QTransform;
  QTransform *gasTransDL = new QTransform;
  QTransform *gasTransDR = new QTransform;

  Controller *root;
  QList<QTransform *> *explodeList;
  float explodeTime;

private:
  void removeDefaultMaterial(const QString &entityName);
  void initMaterials();
  void checkTailFire(const int &direct);
  float noise(const float &orgFLT);
  float noise(const float &low, const float &high);
  void boundingBox(const QString &entityName);
private slots:
  void loadingStatusChanged(QSceneLoader::Status status);
};

#endif // SPACESHIP_H
