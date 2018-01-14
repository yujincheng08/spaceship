#include "cameracontroller.h"
#include "scene.h"
#include "spaceship.h"
#include <QCamera>
#include <QVector3D>

inline float clampInputs(float input1, float input2) {
  float axisValue = input1 + input2;
  return (axisValue < -1) ? -1 : (axisValue > 1) ? 1 : axisValue;
}

inline float zoomDistance(QVector3D firstPoint, QVector3D secondPoint) {
  return (secondPoint - firstPoint).lengthSquared();
}

void CameraController::setTraceTarget(SpaceShip *target) {
  this->target = target;
}

void CameraController::setCursorLock(bool lock) {
  if (lock) {
    QRect geometry = root->geometry();
    int cx = geometry.x() + geometry.width() / 2,
        cy = geometry.y() + geometry.height() / 2;
    QCursor::setPos(cx, cy);
  }
  cursorLock = lock;
}

bool CameraController::getCursorLock() { return cursorLock; }

QVector3D CameraController::getToward() {
  Qt3DRender::QCamera *theCamera = camera();
  if (theCamera == nullptr)
    return {0, 0, 0};
  else
    return (theCamera->viewCenter() - theCamera->position()).normalized();
}

QVector3D CameraController::TransPosition(const QVector3D &up,
                                          const QVector3D &twd,
                                          const QVector3D &pos,
                                          const QVector3D &trans) {
  QVector3D left = QVector3D::crossProduct(up, twd);
  return pos + trans.x() * left + trans.y() * up + trans.z() * twd;
}

QVector3D CameraController::getTransPosition(const QVector3D &up,
                                             const QVector3D &twd,
                                             const QVector3D &pos,
                                             const QVector3D &trans) {
  QVector3D left = QVector3D::crossProduct(up, twd);
  float a = left.x(), b = up.x(), c = twd.x(), d = trans.x() - pos.x(),
        e = left.y(), f = up.y(), g = twd.y(), h = trans.y() - pos.y(),
        i = left.z(), j = up.z(), k = twd.z(), l = trans.z() - pos.z();
  float m = b * e - a * f, n = c * e - a * g, o = d * e - a * h,
        p = b * i - a * j, q = c * i - a * k, r = d * i - a * l;
  float y = (o * q - r * n) / (m * q - p * n),
        z = (o * p - r * m) / (n * p - q * m);
  float x;
  if (a != 0)
    x = (d - b * y - c * z) / a;
  else if (e != 0)
    x = (h - f * y - g * z) / e;
  else if (i != 0)
    x = (l - j * y - k * z) / i;
  return {x, y, z};
}

void CameraController::frameAction(float dt) {
  Qt3DRender::QCamera *theCamera = camera();
  if (theCamera == nullptr)
    return;

  // trace the spaceship
  if (target == nullptr)
    return;
  QVector3D targetUp = target->getUp();
  QVector3D targetPos = target->getPostion();
  QVector3D targetTwd = target->getToward();

  theCamera->setPosition(
      TransPosition(targetUp, targetTwd, targetPos, posTrans));
  theCamera->setViewCenter(
      TransPosition(targetUp, targetTwd, targetPos, ctrTrans));
  theCamera->setUpVector(targetUp);

  // player rotate the camera
  if (!cursorLock)
    return;
  if (root == nullptr)
    return;
  QPoint cursor = root->cursor().pos();
  QRect geometry = root->geometry();
  int cx = geometry.x() + geometry.width() / 2,
      cy = geometry.y() + geometry.height() / 2;
  int rx = cursor.x() - cx, ry = cursor.y() - cy;
  QCursor::setPos(cx, cy);

  theCamera->panAboutViewCenter((-rx * lookSpeed()) * dt / 10, targetUp);

  if (posTrans.y() < 0 && ry < 0)
    ;
  else if (posTrans.y() > posTrans.length() / 1.414 && ry > 0)
    ;
  else
    theCamera->tiltAboutViewCenter((ry * lookSpeed()) * dt / 10);
  posTrans =
      getTransPosition(targetUp, targetTwd, targetPos, theCamera->position());
}
