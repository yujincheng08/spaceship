#include "spaceship.h"

SpaceShip::SpaceShip() {
  isTurnDown = isTurnLeft = isTurnRight = isTurnUp = false;
  isMoveForward = isMoveBack = false;
  setMaxMoveSpeed(1);
  setMaxTurnLRSpeed(1);
  setMaxTurnUDSpeed(1);
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
  double twd[3] = {tx, ty, tz};
  MyVector::unit(twd, 3);
  towardX = twd[0];
  towardY = twd[1];
  towardZ = twd[2];
}

void SpaceShip::setUpDirection(GLdouble ux, GLdouble uy, GLdouble uz) {
  double twd[3] = {towardX, towardY, towardZ}, up[3] = {ux, uy, uz};

  double length =
      MyVector::dotMulti(twd, up, 3) / MyVector::dotMulti(twd, twd, 3);
  MyVector::kMulti(twd, 3, length);
  Vct upVec = MyVector::sub(up, twd, 3);
  MyVector::unit(upVec, 3);

  upX = upVec[0];
  upY = upVec[1];
  upZ = upVec[2];

  delete[] upVec;
}

void SpaceShip::refresh() {
  if (isTurnLeft && !isTurnRight)
    if (turnLRSpeed > -maxTurnLRSpeed)
      turnLRSpeed -= maxTurnLRSpeed / 25;
  if (isTurnRight && !isTurnLeft)
    if (turnLRSpeed < maxTurnLRSpeed)
      turnLRSpeed += maxTurnUDSpeed / 25;
  if (isTurnUp && !isTurnDown)
    if (turnUDSpeed < maxTurnUDSpeed)
      turnUDSpeed += maxTurnUDSpeed / 25;
  if (isTurnDown && !isTurnUp)
    if (turnUDSpeed > -maxTurnUDSpeed)
      turnUDSpeed -= maxTurnUDSpeed / 25;
  qDebug() << this << isMoveForward << isMoveBack << maxMoveSpeed << moveSpeed;
  if (isMoveForward && !isMoveBack)
    if (moveSpeed < maxMoveSpeed) {
      qDebug() << maxMoveSpeed << moveSpeed;
      moveSpeed += maxMoveSpeed / 25;
    }
  if (isMoveBack && !isMoveForward)
    if (moveSpeed > -maxMoveSpeed)
      moveSpeed -= maxMoveSpeed / 25;

  xPos += moveSpeed * towardX;
  yPos += moveSpeed * towardY;
  zPos += moveSpeed * towardZ;
}
