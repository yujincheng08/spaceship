#ifndef OVERLAYMAINWINDOW_H
#define OVERLAYMAINWINDOW_H

#include <QGraphicsOpacityEffect>
#include <QMainWindow>
#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QVector3D>
#include <QWidget>
#include <QWindow>

class Controller;

class OverlayWidget : public QWidget {
  Q_OBJECT

public: // member functions
  // OverlayMainWindow();
  OverlayWidget(Controller *controller, QWidget *parent = 0);
  ~OverlayWidget();

  void setBackgroundWidget(QWidget *backGroundWidget);
  virtual void show();
  void setTransparent(bool transparent);
  void setOpacity(const float &opacity = 0.8);
  void setSpeed(qreal speed) { SpaceshipSpeed = speed; }
  void setPosition(QVector3D pos) { Pos = pos; }
  void setDirection(QVector3D dir) { Dir = dir; }
  void frameAction();

protected: // member functions
  bool eventFilter(QObject *obj, QEvent *event);
  virtual void changeEvent(QEvent *event);
  void paintEvent(QPaintEvent *);

private: // member variables
  QWidget *m_pBackgroundWidget;

  float shootSize = 10;

  float startOpacity = 0, menuOpacity = 0, gamingOpacity = 0, endOpacity = 0;

  Controller *controller;

  QTimer timer;

  qreal SpaceshipSpeed;

  QVector3D Pos;

  QVector3D Dir;
};

#endif // OVERLAYMAINWINDOW_H
