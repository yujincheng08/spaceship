#include "spaceship.h"
#include <QtDebug>
#include <QtMath>

SpaceShip::SpaceShip(QNode *parent) : Component(parent) {
  mesh->setSource(QUrl("qrc:/assets/fj.obj"));
  textureImage->setSource(QUrl("qrc:/assets/img/earthmap2k.jpg"));
  texture->addTextureImage(textureImage);
  material->setTexture(texture);
  addComponent(transform);
  addComponent(mesh);
  addComponent(material);
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

// void SpaceShip::setMaxTurnLRSpeed(GLdouble LR) { maxTurnLRSpeed = LR; }

// void SpaceShip::setMaxTurnUDSpeed(GLdouble UD) { maxTurnUDSpeed = UD; }

// void SpaceShip::setMaxMoveSpeed(GLdouble M) { maxMoveSpeed = M; }

// void SpaceShip::setTowardDirection(GLdouble tx, GLdouble ty, GLdouble tz) {
//  QVector3D twd{tx, ty, tz};
//  twd.normalize();
//  originTX = towardX = twd.x();
//  originTY = towardY = twd.y();
//  originTZ = towardZ = twd.z();
//}

// void SpaceShip::setUpDirection(const QVector3D &up) {
//  QVector3D twd{towardX, towardY, towardZ};
//  QVector3D up{ux, uy, uz};
//  twd *= twd * up;
//  up = up - twd;
//  up.normalize();
//  originUX = upX = up.x();
//  originUY = upY = up.y();
//  originUZ = upZ = up.z();
//}

// void SpaceShip::refresh() {
//  if (isTurnLeft && !isTurnRight)
//    if (turnLRSpeed > -maxTurnLRSpeed)
//      turnLRSpeed -= maxTurnLRSpeed / 25;
//  if (isTurnRight && !isTurnLeft)
//    if (turnLRSpeed < maxTurnLRSpeed)
//      turnLRSpeed += maxTurnUDSpeed / 25;
//  if (isTurnUp && !isTurnDown)
//    if (turnUDSpeed < maxTurnUDSpeed)
//      turnUDSpeed += maxTurnUDSpeed / 25;
//  if (isTurnDown && !isTurnUp)
//    if (turnUDSpeed > -maxTurnUDSpeed)
//      turnUDSpeed -= maxTurnUDSpeed / 25;
//  if (isMoveForward && !isMoveBack)
//    if (moveSpeed < maxMoveSpeed)
//      moveSpeed += maxMoveSpeed / 25;
//  if (isMoveBack && !isMoveForward)
//    if (moveSpeed > -maxMoveSpeed)
//      moveSpeed -= maxMoveSpeed / 25;

//  QVector3D T{towardX, towardY, towardZ};
//  QVector3D U{upX, upY, upX};
//  QVector3D LR = QVector3D::crossProduct(T, U);
//  LR.normalize();
//  LR *= turnLRSpeed;
//  U *= turnUDSpeed;
//  QVector3D unionChange = LR + U;
//  unionChange /= 20;
//  towardX += unionChange.x();
//  towardY += unionChange.y();
//  towardZ += unionChange.z();

//  QVector3D twd{towardX, towardY, towardZ};
//  QVector3D up{upX, upY, upZ};
//  twd.normalize();
//  towardX = twd.x();
//  towardY = twd.y();
//  towardZ = twd.z();
//  twd *= twd * up;
//  QVector3D upVec = up - twd;
//  upVec.normalize();
//  upX = upVec.x();
//  upY = upVec.y();
//  upZ = upVec.z();
//  xPos += moveSpeed * towardX;
//  yPos += moveSpeed * towardY;
//  zPos += moveSpeed * towardZ;
//}

// void SpaceShip::repaint() {

//  /*glBindTexture(GL_TEXTURE_2D, spaceship->texID);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, spaceship->width,
//  spaceship->height,
//                    GL_RGB, GL_UNSIGNED_BYTE, spaceship->data);*/

//  glPushMatrix();
//  glTranslated(xPos, yPos, zPos);

//  // glBindTexture(GL_TEXTURE_2D, earth->texID);

//  spaceshipRotate();

//  glColor3f(r / 255.0, g / 255.0, b / 255.0);
//  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//  glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

//  for (int i = 0; i < F.size(); i++) {
//    glBegin(GL_TRIANGLES);
//    for (int j = 0; j < 3; j++) {
//      if (VT.size() != 0)
//        glTexCoord2f(VT[F[i].T[j]].TU, VT[F[i].T[j]].TV);
//      if (VN.size() != 0)
//        glNormal3f(VN[F[i].N[j]].NX, VN[F[i].N[j]].NY, VN[F[i].N[j]].NZ);
//      glVertex3f(V[F[i].V[j]].X, V[F[i].V[j]].Y, V[F[i].V[j]].Z);
//    }
//    glEnd();
//  }

//  glPopMatrix();
//}

// void SpaceShip::spaceshipRotate() {
//  QVector3D orgT{originTX, originTY, originTZ};
//  QVector3D T{towardX, towardY, towardZ};

//  QVector3D axis = QVector3D::crossProduct(orgT, T);
//  T.normalize();
//  orgT.normalize();
//  GLdouble ang = qAcos(QVector3D::dotProduct(T, orgT));
//  if (ang < 0)
//    ang = ang + M_PI + M_PI;
//  glRotated(ang / M_PI * 180, axis.x(), axis.y(), axis.z());
//}
