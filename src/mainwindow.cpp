#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QGLWidget(parent) {
  initParams();
  initWidget();
  initElement();
  initTimer();
}

MainWindow::~MainWindow() {
  makeCurrent();
  doneCurrent();
}

void MainWindow::initializeGL() {
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  loadTextures();
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0, 0.0, 1.0, 0.5);
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
  setGeometry(0, 27, 960, 540);
  setWindowTitle(tr("War of Spaceship"));
}

void MainWindow::initElement() {
  camera = new MyCamera();
  Component spaceship;
  spaceship.setSource(":/assets/fj.obj");
  spaceship.setColor(36, 40, 51);
  components.insert(components.begin(), spaceship);
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

  vector<Component>::iterator t;
  for (t = components.begin(); t != components.end(); t++) {
    t->repaint();
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
  switch (e->key()) {
  case Qt::Key_Up:
    camera->viewRotate(0, 5);
    updateGL();
    break;
  case Qt::Key_Down:
    camera->viewRotate(0, -5);
    updateGL();
    break;
  case Qt::Key_Left:
    camera->viewRotate(-5, 0);
    updateGL();
    break;
  case Qt::Key_Right:
    camera->viewRotate(5, 0);
    updateGL();
    break;

  case Qt::Key_A:
    camera->posMove(-1, 0, 0);
    updateGL();
    break;
  case Qt::Key_D:
    camera->posMove(1, 0, 0);
    updateGL();
    break;
  case Qt::Key_W:
    camera->posMove(0, 1, 0);
    updateGL();
    break;
  case Qt::Key_S:
    camera->posMove(0, -1, 0);
    updateGL();
    break;
  case Qt::Key_Z:
    camera->posMove(0, 0, 1);
    updateGL();
    break;
  case Qt::Key_X:
    camera->posMove(0, 0, -1);
    updateGL();
    break;

  case Qt::Key_P:
    if (timer.isActive())
      timer.stop();
    else
      timer.start(20, this);
    break;
  }
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton)
    isMousePresseed = 1;
  else if (e->button() == Qt::RightButton)
    isMousePresseed = 2;
  else if (e->button() == Qt::MiddleButton)
    camera->resetView();

  mouse_x = e->x();
  mouse_y = e->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
  switch (isMousePresseed) {
  case 0:
    break;
  case 1:
    camera->viewRotate((e->x() - mouse_x), (e->y() - mouse_y));
    updateGL();
    break;
  case 2:
    camera->viewRound((e->x() - mouse_x), (e->y() - mouse_y));
    updateGL();
    break;
  }

  mouse_x = e->x();
  mouse_y = e->y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) { isMousePresseed = 0; }

void MainWindow::wheelEvent(QWheelEvent *e) {
  if (e->delta() > 0) {
    camera->posMove(0, 0, 1);
    updateGL();
  } else if (e->delta() < 0) {
    camera->posMove(0, 0, -1);
    updateGL();
  }
}

void MainWindow::timerEvent(QTimerEvent *e) {}

void MainWindow::closeEvent(QCloseEvent *e) {}
