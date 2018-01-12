#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "component.h"
#include <QtOpenGL>

class SpaceShip : public Component {
public:
  QSceneLoader *sceneLoader = new QSceneLoader(this);
  QTransform *transform = new QTransform;
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
  void setTowardDirection(const QVector3D &toward) {
    this->toward = toward;
    this->toward.normalize();
  }

  void setUpDirection(const QVector3D &up) {
    this->up = up - toward * up * toward;
    this->up.normalize();
  }

private:
private:
  qreal turnLRSpeed, turnUDSpeed, moveSpeed;
  qreal maxTurnLRSpeed, maxTurnUDSpeed, maxMoveSpeed;

  QVector3D toward;
  QVector3D up;
  qreal towardX, towardY, towardZ, upX, upY, upZ;

  GLboolean isTurnLeft, isTurnRight, isTurnUp, isTurnDown, isMoveForward,
      isMoveBack;
  virtual ~SpaceShip() {}
};

#endif // SPACESHIP_H
