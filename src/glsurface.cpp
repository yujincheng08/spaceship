#include "mainwindow.h"
#include "spaceship.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QGLWidget(parent) {
  qDebug() << "construct for mw";
  initParams();
  initWidget();
  initElement();
  initTimer();
}

MainWindow::~MainWindow() {
  makeCurrent();
  for (int i = 0; i < components.length(); i++)
    delete components.at(i);
  delete cursorTimer;
  doneCurrent();
}

void MainWindow::initializeGL() {
  qDebug() << "initGL start";
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  loadTextures();
  glShadeModel(GL_SMOOTH);
  glClearColor(18 / 255.0, 20 / 255.0, 20 / 255.0, 0.5);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  initLight();
}

void MainWindow::initParams() {
  isMousePresseed = 0;
  mouse_x = mouse_y = 0;
}

void MainWindow::initWidget() {
  qDebug() << "initWidget start!";
  setGeometry(0, 27, 960, 540);
  setWindowTitle(tr("War of Spaceship"));

  // reference: tieba.baidu.com/p/3879195450
  cursorTimer = new QTimer(this);
  QPoint center(this->width() / 2, this->height() / 2);
  QCursor cur = this->cursor();
  cur.setShape(Qt::BlankCursor);
  this->setCursor(cur);

  connect(cursorTimer, &QTimer::timeout, [=]() {
    static bool isFirst = true;

    QPoint offet = QPoint(QCursor::pos() - this->pos()) - center;
    camera->viewRound(offet.x(), offet.y());
    updateGL();
    if (isFirst) {
      offet.setX(0);
      offet.setY(0);
      isFirst = false;
    }
    QCursor::setPos(this->x() + this->width() / 2,
                    this->y() + this->height() / 2);
  });
  cursorTimer->start(10);

  qDebug() << "initWidget successfully!";
}

void MainWindow::initElement() {
  camera = new MyCamera();
  qDebug() << "camera construct successfully!";

  SpaceShip *spaceship = new SpaceShip();
  qDebug() << "spaceship construct successfully!";
  spaceship->setSource(":/assets/fj.obj");
  spaceship->setColor(128, 128, 128);
  spaceship->setTowardDirection(0, 0, -1);
  spaceship->setUpDirection(0, 1, 0);
  spaceship->setMaxMoveSpeed(1);
  qDebug() << "spaceship set successfully!";
  components.append(spaceship);
  qDebug() << "spaceship add successfully!";

  camera->traceComponent(spaceship, 3);
  qDebug() << "camera trace successfully!";

  Component *compare = new Component();
  compare->copySourceFrom(spaceship);
  compare->setColor(128, 128, 128);
  compare->setPosition(0, 10, 0);
  components.append(compare);
  qDebug() << "initElement successfully!";
}

void MainWindow::initTimer() { timer.start(20, this); }

void MainWindow::initLight() {
  MyLight *a = new MyLight(GL_LIGHT0);
  lights.insert(lights.begin(), *a);
}

void MainWindow::loadTextures() {}

void MainWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (camera != NULL)
    camera->setView();

  QList<Component *>::iterator t;
  for (t = components.begin(); t != components.end(); t++) {
    (*t)->repaint();
  }
}

void MainWindow::resizeGL(int width, int height) {
  if (0 == height) {
    height = 1;
  }

  glViewport(0, 0, (GLint)width, (GLint)height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 500);

  if (camera != NULL)
    camera->setView();
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->isAutoRepeat())
    return;
  SpaceShip *a = (SpaceShip *)(components[0]);
  switch (e->key()) {
  case Qt::Key_A:
    a->startTurnLeft();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_D:
    a->startTurnRight();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_W:
    a->startMoveForward();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_S:
    a->startMoveBack();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_E:
    a->startTurnUp();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_C:
    a->startTurnDown();
    camera->keepTrace();
    updateGL();
    break;

  case Qt::Key_P:
    if (timer.isActive()) {
      timer.stop();
      cursorTimer->stop();
    } else {
      timer.start(20, this);
      cursorTimer->start(10);
    }
    break;
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) {
  if (e->isAutoRepeat())
    return;
  SpaceShip *a = (SpaceShip *)(components[0]);
  switch (e->key()) {
  case Qt::Key_A:
    a->endTurnLeft();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_D:
    a->endTurnRight();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_W:
    a->endMoveForward();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_S:
    a->endMoveBack();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_E:
    a->endTurnUp();
    camera->keepTrace();
    updateGL();
    break;
  case Qt::Key_C:
    a->endTurnDown();
    camera->keepTrace();
    updateGL();
    break;
  }
}

// void MainWindow::mousePressEvent(QMouseEvent *e) {
//  if (e->button() == Qt::LeftButton)
//    isMousePresseed = 1;
//  else if (e->button() == Qt::RightButton)
//    isMousePresseed = 2;
//  else if (e->button() == Qt::MiddleButton)
//    camera->resetView();

//  mouse_x = e->x();
//  mouse_y = e->y();
//}

// void MainWindow::mouseMoveEvent(QMouseEvent *e) {
//  switch (isMousePresseed) {
//  case 0:
//    break;
//  case 1:
//    camera->viewRotate((e->x() - mouse_x), (e->y() - mouse_y));
//    updateGL();
//    break;
//  case 2:

//    break;
//  }

//  mouse_x = e->x();
//  mouse_y = e->y();
//}

// void MainWindow::mouseReleaseEvent(QMouseEvent *e) { isMousePresseed = 0; }

void MainWindow::wheelEvent(QWheelEvent *e) {
  if (e->delta() > 0) {
    camera->posMove(0, 0, 3);
    updateGL();
  } else if (e->delta() < 0) {
    camera->posMove(0, 0, -3);
    updateGL();
  }
}

void MainWindow::timerEvent(QTimerEvent *e) {
  SpaceShip *a = (SpaceShip *)(components[0]);
  a->refresh();
  camera->keepTrace();
  updateGL();
}

void MainWindow::closeEvent(QCloseEvent *e) {}