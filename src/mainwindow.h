#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "component.h"
#include "mycamera.h"
#include "mylight.h"
#include <QBasicTimer>
#include <QVector>
#include <Qt3DExtras>
#include <QtOpenGL>
#include <scene.h>

class InfoSurface;

class MainWindow : public QMainWindow {
  friend class InfoSurface;

public:
  using Qt3DWindow = Qt3DExtras::Qt3DWindow;

private:
  Scene *scene = new Scene;
  QWidget *container = QWidget::createWindowContainer(scene, this);

public:
  MainWindow(QWidget *parent = nullptr);
  virtual ~MainWindow() final;

protected:
  //  void initParams();
  //  void initWidget();
  //  void initElement();
  //  void initTimer();
  //  void initLight();
  //  void loadTextures();
  //  void initializeGL();
  // void paintGL() override;
  // void resizeGL(int width, int height) override;

  //  void paintEvent(QPaintEvent *e);

  //  //  void mousePressEvent(QMouseEvent *e) override;
  //  //  void mouseMoveEvent(QMouseEvent *e) override;
  //  //  void mouseReleaseEvent(QMouseEvent *e) override;
  //  void wheelEvent(QWheelEvent *e) override;
  //  void timerEvent(QTimerEvent *e) override;

  //  void closeEvent(QCloseEvent *e) override;

private:
  void initScene(const QColor &clearColor = QColor(QRgb(0x4d4d4f)));

  int isMousePresseed;
  double mouse_x, mouse_y;

  QBasicTimer timer;
  QTimer *cursorTimer;

  InfoSurface *is;
};

#endif // MAINWINDOW_H
