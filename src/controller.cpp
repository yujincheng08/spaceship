#include "controller.h"

OverlayWidget *Controller::getInfoSurface() const { return infoSurface; }

bool Controller::isCollision(const QList<BoundingBox> &a,
                             const QList<BoundingBox> &b) {
  for (BoundingBox boxa : a)
    for (BoundingBox boxb : b)
      if (boxCollision(boxa, boxb))
        return true;
  return false;
}

bool Controller::isCollision(const QList<BoundingBox> &a,
                             const QVector3D &point) {
  for (BoundingBox box : a) {
    if (pointCollision(box.point, box.x, point) == 0 &&
        pointCollision(box.point, box.y, point) == 0 &&
        pointCollision(box.point, box.z, point) == 0)
      return true;
  }
  return false;
}

bool Controller::isCollision(const QList<BoundingBox> &a,
                             const QVector3D &center, const float &r) {
  for (BoundingBox box : a)
    if (boxCollision(box, center, r))
      return true;
  return false;
}

bool Controller::isCollision(const QVector3D &point, const QVector3D &center,
                             const float &r) {
  return (center - point).length() < r;
}

void Controller::frameAction(float) {
  // orbit
  earth->orbit(sun);
  moon->orbit(earth);
  mercury->orbit(sun);
  venus->orbit(sun);
  mars->orbit(sun);
  neptune->orbit(sun);
  jupiter->orbit(sun);
  saturn->orbit(sun);
  uranus->orbit(sun);

  // state control

  // bullet

  // collison test
}

bool Controller::boxCollision(const BoundingBox &a, const BoundingBox &b) {
  bool xCollision = lineCollision(a.point, a.x, b),
       yCollision = lineCollision(a.point, a.y, b),
       zCollision = lineCollision(a.point, a.z, b);
  return xCollision && yCollision && zCollision;
}

bool Controller::boxCollision(const BoundingBox &a, const QVector3D &center,
                              const float &r) {
  Q_UNUSED(r)
  if (pointCollision(a.point, a.x, center) == 0 &&
      pointCollision(a.point, a.y, center) == 0 &&
      pointCollision(a.point, a.z, center) == 0)
    return true;
  QVector3D checkpoint;
  for (int i = 0; i < 8; i++) {
    checkPoint = a.point;
    if ((i & 1) != 0)
      checkPoint += a.x;
    if ((i & 2) != 0)
      checkPoint += a.y;
    if ((i & 4) != 0)
      checkPoint += a.z;
    if ((center - checkpoint).length() < r)
      return true;
  }
  return false;
}

bool Controller::lineCollision(const QVector3D &point, const QVector3D &line,
                               const BoundingBox &box) {
  bool left = false, right = false;
  QVector3D checkPoint;

  for (int i = 0; i < 8; i++) {
    checkPoint = box.point;
    if ((i & 1) != 0)
      checkPoint += box.x;
    if ((i & 2) != 0)
      checkPoint += box.y;
    if ((i & 4) != 0)
      checkPoint += box.z;
    switch (pointCollision(point, line, checkPoint)) {
    case 0:
      return true;
    case 1:
      left = true;
      break;
    case 2:
      right = true;
      break;
    }

    if (left && right)
      return true;
  }
  return false;
}

int Controller::pointCollision(const QVector3D &point, const QVector3D &line,
                               const QVector3D &check) {

  QVector3D a = check - point;
  if (QVector3D::dotProduct(a, line) <= 0)
    return 1;
  a -= line;
  if (QVector3D::dotProduct(a, line) >= 0)
    return 2;

  return 0;
}

void Controller::initInput() {
  mouseHandler->setSourceDevice(mouseDevice);
  connect(mouseHandler, &QMouseHandler::pressed, this, [&](QMouseEvent *) {
    if (state == GAMING)
      spaceship->startShoot();
  });
  connect(mouseHandler, &QMouseHandler::released, this, [&](QMouseEvent *) {
    if (state == GAMING)
      spaceship->endShoot();
  });
  upActionInput->setButtons(QVector<int>() << Qt::Key_W << Qt::Key_Up);
  upActionInput->setSourceDevice(keyboardDevice);
  upAction->addInput(upActionInput);
  connect(upAction, &QAction::activeChanged, this, [&](bool active) {
    if (state != GAMING)
      return;
    if (active)
      spaceship->startMoveForward();
    else
      spaceship->endMoveForward();
  });
  downActionInput->setButtons(QVector<int>() << Qt::Key_S << Qt::Key_Down);
  downActionInput->setSourceDevice(keyboardDevice);
  downAction->addInput(downActionInput);
  connect(downAction, &QAction::activeChanged, this, [&](bool active) {
    if (state != GAMING)
      return;
    if (active)
      spaceship->startMoveBack();
    else
      spaceship->endMoveBack();
  });
  leftActionInput->setButtons(QVector<int>() << Qt::Key_A << Qt::Key_Left);
  leftActionInput->setSourceDevice(keyboardDevice);
  leftAction->addInput(leftActionInput);
  connect(leftAction, &QAction::activeChanged, this, [&](bool active) {
    if (state != GAMING)
      return;
    if (active)
      spaceship->startTurnLeft();
    else
      spaceship->endTurnLeft();
  });
  rightActionInput->setButtons(QVector<int>() << Qt::Key_D << Qt::Key_Right);
  rightActionInput->setSourceDevice(keyboardDevice);
  rightAction->addInput(rightActionInput);
  connect(rightAction, &QAction::activeChanged, this, [&](bool active) {
    if (state != GAMING)
      return;
    if (active)
      spaceship->startTurnRight();
    else
      spaceship->endTurnRight();
  });
  forwardActionInput->setButtons(QVector<int>() << Qt::Key_E << Qt::Key_PageUp);
  forwardActionInput->setSourceDevice(keyboardDevice);
  forwardAction->addInput(forwardActionInput);
  connect(forwardAction, &QAction::activeChanged, this, [&](bool active) {
    if (state != GAMING)
      return;
    if (active)
      spaceship->startTurnUp();
    else
      spaceship->endTurnUp();
  });
  backwardActionInput->setButtons(QVector<int>() << Qt::Key_C
                                                 << Qt::Key_PageDown);
  backwardActionInput->setSourceDevice(keyboardDevice);
  backwardAction->addInput(backwardActionInput);
  connect(backwardAction, &QAction::activeChanged, this, [&](bool active) {
    if (state != GAMING)
      return;
    if (active)
      spaceship->startTurnDown();
    else
      spaceship->endTurnDown();
  });
  escapeActionInput->setButtons(QVector<int>() << Qt::Key_Escape);
  escapeActionInput->setSourceDevice(keyboardDevice);
  escapeAction->addInput(escapeActionInput);
  connect(escapeAction, &QAction::activeChanged, this, [&](bool active) {
    if (active) {
      if (state == MENU)
        continueGame();
      else if (state == GAMING)
        callOutMenu();
    }
  });
  enterActionInput->setButtons(QVector<int>() << Qt::Key_Enter
                                              << Qt::Key_Return);
  enterActionInput->setSourceDevice(keyboardDevice);
  enterAction->addInput(enterActionInput);
  connect(enterAction, &QAction::activeChanged, this, [&](bool active) {
    if (active) {
      if (state == START || state == END)
        startGame();
    }
  });

  logicalDevice->addAction(upAction);
  logicalDevice->addAction(downAction);
  logicalDevice->addAction(leftAction);
  logicalDevice->addAction(rightAction);
  logicalDevice->addAction(forwardAction);
  logicalDevice->addAction(backwardAction);
  logicalDevice->addAction(escapeAction);
  logicalDevice->addAction(enterAction);
}

void Controller::initScene() {
  initCamera();
  initPlanets();
  initSpaceship();
  initLight();
  initFrameAction();
}

void Controller::initCamera() {
  scene->camera()->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f,
                                                    20000000.0f);
  scene->camera()->setPosition(QVector3D(0, 0, -20.0f));
  scene->camera()->setViewCenter(QVector3D(0, 0, 0));
  cameraController->setTraceTarget(spaceship);
  cameraController->setCursorLock(false);
  cameraController->setCamera(scene->camera());
}

void Controller::initPlanets() {
  earth->setPosition(earth->getOriginPosition());
  sun->setPosition(sun->getOriginPosition());
  mercury->setPosition(mercury->getOriginPosition());
  venus->setPosition(venus->getOriginPosition());
  moon->setPosition(moon->getOriginPosition());
  mars->setPosition(mars->getOriginPosition());
  jupiter->setPosition(jupiter->getOriginPosition());
  saturn->setPosition(saturn->getOriginPosition());
  uranus->setPosition(uranus->getOriginPosition());
  neptune->setPosition(neptune->getOriginPosition());
}

void Controller::initSpaceship() {
  spaceship->setInitialDirection({0, 0, -1}, {0, 1, 0});
}

void Controller::initLight() {
  // dummy
}

void Controller::initFrameAction() {
  connect(frame, &QFrameAction::triggered, scene, &Scene::frameAction);
  connect(frame, &QFrameAction::triggered, spaceship, &Component::frameAction);
  connect(frame, &QFrameAction::triggered, cameraController,
          &CameraController::frameAction);
  connect(frame, &QFrameAction::triggered, this, &Controller::frameAction);
}

void Controller::continueGame() {
  cameraController->setCursorLock(true);
  frame->blockSignals(false);
  state = GAMING;
}

void Controller::callOutMenu() {
  cameraController->setCursorLock(false);
  frame->blockSignals(true);
  state = MENU;
}

void Controller::startGame() {
  cameraController->setCursorLock(true);
  frame->blockSignals(false);
  state = GAMING;
}

void Controller::addLaserBullet(const QVector3D &pos,
                                const QVector3D &velocity) {
  LaserBullet *bullet = new LaserBullet(pos, velocity, scene, this);
  connect(frame, &QFrameAction::triggered, bullet, &Component::frameAction);
}

void Controller::addLaserBullet(const QVector3D &pos, const float &speed) {
  addLaserBullet(pos, speed * cameraController->getToward());
}

void Controller::removeLaserBullet(LaserBullet *bullet) {
  disconnect(frame, &QFrameAction::triggered, bullet, &Component::frameAction);
  delete bullet;
}

void Controller::spaceshipExplode(SpaceShip *spaceship) {
  disconnect(frame, &QFrameAction::triggered, spaceship,
             &Component::frameAction);
  if (spaceship == this->spaceship)
    gameOver();

  delete spaceship;
}

void Controller::gameOver() {
  cameraController->setCursorLock(false);
  state = END;
}
