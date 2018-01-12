#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "component.h"
#include <QSceneChange>
#include <QtOpenGL>

class SpaceShip : public Component {
public:
  QMesh *mesh = new QMesh(this);
  QTextureMaterial *material = new QTextureMaterial;
  QTextureImage *textureImage = new QTextureImage;
  QTexture2D *texture = new QTexture2D;

  friend class InfoSurface;
  SpaceShip(QNode *parent = nullptr);
  void startTurnLeft();
  void startTurnRight();
  void startTurnUp();
  void startTurnDown();
  void startMoveForward();
  void startMoveBack();
  void endTurnLeft();
  void endTurnRight();
  void endTurnUp();
  void endTurnDown();
  void endMoveForward();
  void endMoveBack();

  void setMaxTurnLRSpeed(qreal speed) { maxTurnLRSpeed = speed; }
  void setMaxTurnUDSpeed(qreal speed) { maxTurnUDSpeed = speed; }
  void setMaxMoveSpeed(qreal speed) { maxMoveSpeed = speed; }
  void setInitialDirection(const QVector3D &toward, const QVector3D &up) {
    initDir = QQuaternion::fromDirection(toward, up);
    transform->setRotation(initDir);
  }

  QVector3D getToward();
  QVector3D getUp();

protected slots:
  virtual void frameAction(float dt) override;

private:
  qreal turnLRSpeed, turnUDSpeed, moveSpeed;
  qreal maxTurnLRSpeed, maxTurnUDSpeed, maxMoveSpeed;

  QQuaternion initDir;

  GLboolean isTurnLeft, isTurnRight, isTurnUp, isTurnDown, isMoveForward,
      isMoveBack;
  virtual ~SpaceShip() {}
};

#endif // SPACESHIP_H
