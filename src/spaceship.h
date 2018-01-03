#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "component.h"
#include "vector.h"
#include <QtOpenGL>

class SpaceShip : public Component {
public:
  SpaceShip();
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

  void setMaxTurnLRSpeed(GLdouble LR);
  void setMaxTurnUDSpeed(GLdouble UD);
  void setMaxMoveSpeed(GLdouble M);
  void setTowardDirection(GLdouble tx, GLdouble ty, GLdouble tz);
  void setUpDirection(GLdouble ux, GLdouble uy, GLdouble uz);

  void refresh();

public:
  GLdouble turnLRSpeed, turnUDSpeed, moveSpeed;
  GLdouble maxTurnLRSpeed, maxTurnUDSpeed, maxMoveSpeed;
  GLdouble towardX, towardY, towardZ, upX, upY, upZ;

  GLboolean isTurnLeft, isTurnRight, isTurnUp, isTurnDown, isMoveForward,
      isMoveBack;
};

#endif // SPACESHIP_H
