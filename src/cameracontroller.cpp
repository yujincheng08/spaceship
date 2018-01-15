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

void CameraController::setCursorLock(bool lock) {
  if (lock) {
    QRect geometry = root->geometry();
    int cx = geometry.x() + geometry.width() / 2,
        cy = geometry.y() + geometry.height() / 2;
    QCursor::setPos(cx, cy);
    if (root)
      root->setCursor(Qt::BlankCursor);
  } else if (root)
    root->setCursor(Qt::ArrowCursor);
  cursorLock = lock;
}

QVector3D CameraController::getToward() {
  if (camera == nullptr)
    return {0, 0, 0};
  else
    return (camera->viewCenter() - camera->position()).normalized();
}

void CameraController::zoom(const bool &direction) {
  QVector3D dis = posTrans - ctrTrans;
  float dist = dis.length();
  if (!direction && dist > 9)
    dist -= 0.5;
  if (direction && dist < 40)
    dist += 0.5;
  posTrans = ctrTrans + dis.normalized() * dist;
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
  if (isRelease) {
    camera->setPosition(
        (camera->position() - camera->viewCenter()).normalized() *
            ((camera->position() - camera->viewCenter()).length() + dt) +
        camera->viewCenter());
  }

  if (camera == nullptr)
    return;

  // trace the spaceship
  if (target == nullptr)
    return;
  auto targetUp = target->getUp();
  auto targetPos = target->getPostion();
  auto targetTwd = target->getToward();

  camera->setPosition(TransPosition(targetUp, targetTwd, targetPos, posTrans));
  camera->setViewCenter(
      TransPosition(targetUp, targetTwd, targetPos, ctrTrans));
  camera->setUpVector(targetUp);

  // player rotate the camera
  if (!cursorLock)
    return;
  if (root && !root->isActive()) {
    isActived = false;
    return;
  }
  QRect geometry = root->geometry();
  int cx = geometry.x() + geometry.width() / 2,
      cy = geometry.y() + geometry.height() / 2;
  if (!isActived) {
    QCursor::setPos(cx, cy);
  }
  isActived = true;
  QPoint cursor = root->cursor().pos();
  int rx = cursor.x() - cx, ry = cursor.y() - cy;
  QCursor::setPos(cx, cy);

  camera->panAboutViewCenter(-rx * dt * 2, targetUp);

  if (!(posTrans.y() < 0 && ry < 0) &&
      !(posTrans.y() > posTrans.length() / 1.414 && ry > 0))
    camera->tiltAboutViewCenter(ry * dt * 2);
  posTrans =
      getTransPosition(targetUp, targetTwd, targetPos, camera->position());
}
