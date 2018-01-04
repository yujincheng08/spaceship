#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "component.h"
#include "mycamera.h"
#include "mylight.h"
#include <GL/glut.h>
#include <QBasicTimer>
#include <QVector>
#include <QtOpenGL>

class MainWindow : public QOpenGLWidget {
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  void initParams();
  void initWidget();
  void initElement();
  void initTimer();
  void initLight();
  void loadTextures();
  void initializeGL();
  void paintGL() override;
  void resizeGL(int width, int height) override;

  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;
  //  void mousePressEvent(QMouseEvent *e) override;
  //  void mouseMoveEvent(QMouseEvent *e) override;
  //  void mouseReleaseEvent(QMouseEvent *e) override;
  void wheelEvent(QWheelEvent *e) override;
  void timerEvent(QTimerEvent *e) override;

  void closeEvent(QCloseEvent *e) override;

private:
  MyCamera *camera;

  QList<MyLight> lights;
  QList<Component *> components;

  int isMousePresseed;
  double mouse_x, mouse_y;

  QBasicTimer timer;
  QTimer *cursorTimer;
};

#endif // MAINWINDOW_H
