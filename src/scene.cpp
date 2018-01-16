#include "scene.h"
#include <Qt3DRender/QCamera>

Scene::Scene(QScreen *parent) : Qt3DExtras::Qt3DWindow(parent) {
  setRootEntity(root);
}

// void Scene::addLaserBullet(const QVector3D &pos, const QVector3D &velocity) {
//  LaserBullet *bullet = new LaserBullet(pos, velocity, root, this);
//  connect(frame, &QFrameAction::triggered, bullet, &Component::frameAction);
//}

// void Scene::addLaserBullet(const QVector3D &pos, const float &speed) {
//  addLaserBullet(pos, speed * controller->getToward());
//}

// void Scene::spaceshipExplode(SpaceShip *spaceship) {
//  disconnect(frame, &QFrameAction::triggered, spaceship,
//             &Component::frameAction);
//  if (spaceship == this->spaceship)
//    gameOver();

//  delete spaceship;
//}

// void Scene::gameOver() { qDebug() << "Game Over"; }

// void Scene::frameAction(float) {
//  if (spaceship->isExplode())
//    controller->release();
//}

// void Scene::keyPressEvent(QKeyEvent *e) {
//  Qt3DExtras::Qt3DWindow::keyPressEvent(e);
//  if (e->isAutoRepeat())
//    return;
//  SpaceShip *a = spaceship;
//  switch (e->key()) {
//  case Qt::Key_A:
//    a->startTurnLeft();
//    break;
//  case Qt::Key_D:
//    a->startTurnRight();
//    break;
//  case Qt::Key_W:
//    a->startMoveForward();
//    break;
//  case Qt::Key_S:
//    a->startMoveBack();
//    break;
//  case Qt::Key_E:
//    a->startTurnUp();
//    break;
//  case Qt::Key_C:
//    a->startTurnDown();
//    break;

//  case Qt::Key_B:
//    spaceship->explode();
//    break;

//  case Qt::Key_Escape:
//    controller->setCursorLock(!(controller->getCursorLock()));
//    break;
//  case Qt::Key_P:
//    //    if (timer.isActive()) {
//    //      timer.stop();
//    //      cursorTimer->stop();
//    //    } else {
//    //      timer.start(20, this);
//    //      cursorTimer->start(10);
//    //    }
//    break;
//  }
//}

// void Scene::keyReleaseEvent(QKeyEvent *e) {
//  Qt3DExtras::Qt3DWindow::keyReleaseEvent(e);
//  if (e->isAutoRepeat())
//    return;
//  SpaceShip *a = spaceship;
//  switch (e->key()) {
//  case Qt::Key_A:
//    a->endTurnLeft();
//    break;
//  case Qt::Key_D:
//    a->endTurnRight();
//    break;
//  case Qt::Key_W:
//    a->endMoveForward();
//    break;
//  case Qt::Key_S:
//    a->endMoveBack();
//    break;
//  case Qt::Key_E:
//    a->endTurnUp();
//    break;
//  case Qt::Key_C:
//    a->endTurnDown();
//    break;
//  }
//}

// void Scene::mousePressEvent(QMouseEvent *) {
//  if (controller->getCursorLock())
//    spaceship->startShoot();
//}

// void Scene::mouseReleaseEvent(QMouseEvent *) {
//  if (controller->getCursorLock())
//    spaceship->endShoot();
//}

// void Scene::wheelEvent(QWheelEvent *e) { controller->zoom(e->delta() < 0); }
