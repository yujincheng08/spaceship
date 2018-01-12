#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <GL/glut.h>
#include <QtOpenGL>

class Component;

class MyCamera {
public:
  MyCamera();
  void setView();
  void resetView();
  void setEye(const QVector3D &eye);
  void setCenter(const QVector3D &center);
  void setUp(const QVector3D &up);
  void traceComponent(const Component *cpnt, GLdouble off = 0);
  void keepTrace();
  void posMove(const QVector3D &shift);
  void viewRotate(qreal lr, qreal ud);
  void viewRound(qreal lr, qreal ud);

private:
  QVector3D eye;
  QVector3D center;
  QVector3D up;
  qreal offset;

  const Component *trace;

  qreal step, rotate;
};

#endif // MYCAMARA_H
