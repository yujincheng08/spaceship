#include "spaceship.h"

SpaceShip::SpaceShip() {
  isTurnDown = isTurnLeft = isTurnRight = isTurnUp = false;
  isMoveForward = isMoveBack = false;
  maxTurnLRSpeed = maxTurnUDSpeed = maxMoveSpeed = 1;
  turnLRSpeed = turnUDSpeed = moveSpeed = 0;
  towardX = 1;
  towardY = 0;
  towardZ = 0;
  upX = 0;
  upY = 0;
  upZ = 1;
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

void SpaceShip::setMaxTurnLRSpeed(GLdouble LR) { maxTurnLRSpeed = LR; }

void SpaceShip::setMaxTurnUDSpeed(GLdouble UD) { maxTurnUDSpeed = UD; }

void SpaceShip::setMaxMoveSpeed(GLdouble M) { maxMoveSpeed = M; }

void SpaceShip::setTowardDirection(GLdouble tx, GLdouble ty, GLdouble tz) {
  towardX = tx;
  towardY = ty;
  towardZ = tz;
}

void SpaceShip::setUpDirection(GLdouble ux, GLdouble uy, GLdouble uz) {
  upX = ux;
  upY = uy;
  upZ = uz;
}

void SpaceShip::refresh() {}
