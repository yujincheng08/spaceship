#include "scene.h"
#include <Qt3DRender/QCamera>
Scene::Scene(QScreen *parent) : Qt3DExtras::Qt3DWindow(parent) {
  setRootEntity(root);

  initCamera();

  initPlanets();

  initSpaceship();

  initLight();

  initFrame();
}

void Scene::initCamera() {
  camera()->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f,
                                             20000000.0f);
  camera()->setPosition(QVector3D(0, 0, -20.0f));
  camera()->setViewCenter(QVector3D(0, 0, 0));
  controller->setLinearSpeed(50.0f);
  controller->setLookSpeed(180.0f);
  controller->setCamera(camera());
  controller->setTraceTarget(spaceship);
  controller->setCursorLock(true);
}

void Scene::initPlanets() {
  earth->setPosition({0, 2, 0});
  // sun->setPosition({0, 20, 0});
}

void Scene::initSpaceship() {
  spaceship->setInitialDirection({0, 0, -1}, {0, 1, 0});
}

void Scene::initLight() { light->setPosition({0, 20, 20}); }

void Scene::initFrame() {
  connect(frame, &QFrameAction::triggered, this, &Scene::frameAction);
  connect(frame, &QFrameAction::triggered, spaceship, &Component::frameAction);
  connect(frame, &QFrameAction::triggered, controller,
          &CameraController::frameAction);
}

void Scene::frameAction(float dt) {}

void Scene::keyPressEvent(QKeyEvent *e) {
  Qt3DExtras::Qt3DWindow::keyPressEvent(e);
  if (e->isAutoRepeat())
    return;
  SpaceShip *a = spaceship;
  switch (e->key()) {
  case Qt::Key_A:
    a->startTurnLeft();
    break;
  case Qt::Key_D:
    a->startTurnRight();
    break;
  case Qt::Key_W:
    a->startMoveForward();
    break;
  case Qt::Key_S:
    a->startMoveBack();
    break;
  case Qt::Key_E:
    a->startTurnUp();
    break;
  case Qt::Key_C:
    a->startTurnDown();
    break;

  case Qt::Key_Escape:
    controller->setCursorLock(!(controller->getCursorLock()));
    break;
  case Qt::Key_P:
    //    if (timer.isActive()) {
    //      timer.stop();
    //      cursorTimer->stop();
    //    } else {
    //      timer.start(20, this);
    //      cursorTimer->start(10);
    //    }
    break;
  }
}

void Scene::keyReleaseEvent(QKeyEvent *e) {
  Qt3DExtras::Qt3DWindow::keyReleaseEvent(e);
  if (e->isAutoRepeat())
    return;
  SpaceShip *a = spaceship;
  switch (e->key()) {
  case Qt::Key_A:
    a->endTurnLeft();
    break;
  case Qt::Key_D:
    a->endTurnRight();
    break;
  case Qt::Key_W:
    a->endMoveForward();
    break;
  case Qt::Key_S:
    a->endMoveBack();
    break;
  case Qt::Key_E:
    a->endTurnUp();
    break;
  case Qt::Key_C:
    a->endTurnDown();
    break;
  }
}
