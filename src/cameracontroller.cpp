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

void CameraController::setCursorLock(bool lock) { cursorLock = lock; }

bool CameraController::getCursorLock() { return cursorLock; }

void CameraController::moveCamera(
    const QAbstractCameraController::InputState &state, float dt) {

  Qt3DRender::QCamera *theCamera = camera();
  if (theCamera == nullptr)
    return;

  const QVector3D upVector(0.0f, 1.0f, 0.0f);

  //  // Mouse input
  //  if (state.leftMouseButtonActive) {
  //    if (state.rightMouseButtonActive) {
  //      theCamera->translate(QVector3D(0, 0, state.ryAxisValue),
  //                           theCamera->DontTranslateViewCenter);
  //    } else {
  //      // Translate
  //      theCamera->translate(
  //          QVector3D(
  //              clampInputs(state.rxAxisValue, state.txAxisValue) *
  //              linearSpeed(), clampInputs(state.ryAxisValue,
  //              state.tyAxisValue) * linearSpeed(), 0) *
  //          dt);
  //    }
  //    return;
  //  } else if (state.rightMouseButtonActive) {
  // Orbit
  theCamera->panAboutViewCenter((state.rxAxisValue * lookSpeed()) * dt,
                                upVector);
  theCamera->tiltAboutViewCenter((state.ryAxisValue * lookSpeed()) * dt);
  //  }
}

void CameraController::frameAction(float dt) {
  Qt3DRender::QCamera *theCamera = camera();
  if (theCamera == nullptr)
    return;

  // trace the spaceship
  if (target == nullptr)
    return;
  QVector3D targetUp = target->getUp();

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

  theCamera->panAboutViewCenter((rx * lookSpeed()) * dt, targetUp);
  theCamera->tiltAboutViewCenter((ry * lookSpeed()) * dt);
}
