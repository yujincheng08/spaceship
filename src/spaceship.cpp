#include "spaceship.h"
#include <QtMath>

SpaceShip::SpaceShip() {
  isTurnDown = isTurnLeft = isTurnRight = isTurnUp = false;
  isMoveForward = isMoveBack = false;
  setMaxMoveSpeed(1);
  setMaxTurnLRSpeed(1);
  setMaxTurnUDSpeed(1);
  turnLRSpeed = turnUDSpeed = moveSpeed = 0;
  towardX = 0;
  towardY = 0;
  towardZ = -1;
  upX = 0;
  upY = 1;
  upZ = 0;
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

void SpaceShip::setMaxTurnLRSpeed(GLdouble LR) { maxTurnLRSpeed = LR; }

void SpaceShip::setMaxTurnUDSpeed(GLdouble UD) { maxTurnUDSpeed = UD; }

void SpaceShip::setMaxMoveSpeed(GLdouble M) { maxMoveSpeed = M; }

void SpaceShip::setTowardDirection(GLdouble tx, GLdouble ty, GLdouble tz) {
  double twd[3] = {tx, ty, tz};
  MyVector::unit(twd, 3);
  originTX = towardX = twd[0];
  originTY = towardY = twd[1];
  originTZ = towardZ = twd[2];
}

void SpaceShip::setUpDirection(GLdouble ux, GLdouble uy, GLdouble uz) {
  double twd[3] = {towardX, towardY, towardZ}, up[3] = {ux, uy, uz};

  double length = MyVector::dotMulti(twd, up, 3);
  MyVector::kMulti(twd, 3, length);
  Vct upVec = MyVector::sub(up, twd, 3);
  MyVector::unit(upVec, 3);

  originUX = upX = upVec[0];
  originUY = upY = upVec[1];
  originUZ = upZ = upVec[2];

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
  if (isMoveForward && !isMoveBack)
    if (moveSpeed < maxMoveSpeed)
      moveSpeed += maxMoveSpeed / 25;
  if (isMoveBack && !isMoveForward)
    if (moveSpeed > -maxMoveSpeed)
      moveSpeed -= maxMoveSpeed / 25;

  double T[3] = {towardX, towardY, towardZ}, U[3] = {upX, upY, upZ};
  Vct LR = MyVector::crossMulti3(T, U);
  MyVector::unit(LR, 3);
  MyVector::kMulti(LR, 3, turnLRSpeed);
  MyVector::kMulti(U, 3, turnUDSpeed);
  Vct unionChange = MyVector::add(LR, U, 3);
  delete[] LR;
  towardX += unionChange[0] / 20;
  towardY += unionChange[1] / 20;
  towardZ += unionChange[2] / 20;
  delete[] unionChange;

  double twd[3] = {towardX, towardY, towardZ}, up[3] = {upX, upY, upZ};
  MyVector::unit(twd, 3);
  towardX = twd[0];
  towardY = twd[1];
  towardZ = twd[2];
  double length = MyVector::dotMulti(twd, up, 3);
  MyVector::kMulti(twd, 3, length);
  Vct upVec = MyVector::sub(up, twd, 3);
  MyVector::unit(upVec, 3);
  upX = upVec[0];
  upY = upVec[1];
  upZ = upVec[2];
  delete[] upVec;

  xPos += moveSpeed * towardX;
  yPos += moveSpeed * towardY;
  zPos += moveSpeed * towardZ;
}

void SpaceShip::repaint() {
  glPushMatrix();
  glTranslated(xPos, yPos, zPos);
  spaceshipRotate();

  glColor3f(r / 255.0, g / 255.0, b / 255.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

  for (int i = 0; i < F.size(); i++) {
    glBegin(GL_TRIANGLES);
    for (int j = 0; j < 3; j++) {
      if (VT.size() != 0)
        glTexCoord2f(VT[F[i].T[j]].TU, VT[F[i].T[j]].TV);
      if (VN.size() != 0)
        glNormal3f(VN[F[i].N[j]].NX, VN[F[i].N[j]].NY, VN[F[i].N[j]].NZ);
      glVertex3f(V[F[i].V[j]].X, V[F[i].V[j]].Y, V[F[i].V[j]].Z);
    }
    glEnd();
  }

  glPopMatrix();
}

void SpaceShip::spaceshipRotate() {
  double orgT[3] = {originTX, originTY, originTZ},
         orgU[3] = {originUX, originUY, originUZ},
         T[3] = {towardX, towardY, towardZ}, U[3] = {upX, upY, upZ};

  Vct axis = MyVector::crossMulti3(orgT, T);
  //  qDebug() << "cT" << T[0] << T[1] << T[2];
  //  qDebug() << "oT" << orgT[0] << orgT[1] << orgT[2];
  //  qDebug() << "AX" << axis[0] << axis[1] << axis[2];
  //  qDebug() << "AG" << MyVector::angle(T, orgT, 3);
  GLdouble ang = MyVector::angle(T, orgT, 3);
  if (ang < 0)
    ang = ang + M_PI + M_PI;
  glRotated(ang / M_PI * 180, axis[0], axis[1], axis[2]);
  delete[] axis;
}
