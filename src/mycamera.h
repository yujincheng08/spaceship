#ifndef MYCAMERA_H
#define MYCAMERA_H

#include "vector.h"
#include <GL/glu.h>
#include <QtOpenGL>

class MyCamera {
public:
  MyCamera();
  void setView();
  void resetView();
  void setEye(GLdouble ex, GLdouble ey, GLdouble ez);
  void setCenter(GLdouble cx, GLdouble cy, GLdouble cz);
  void setUp(GLdouble ux, GLdouble uy, GLdouble uz);
  void posMove(GLdouble mx, GLdouble my, GLdouble mz);
  void viewRotate(GLdouble lr, GLdouble ud);
  void viewRound(GLdouble lr, GLdouble ud);

private:
  GLdouble eyex, eyey, eyez;
  GLdouble centerx, centery, centerz;
  GLdouble upx, upy, upz;

  GLdouble step, rotate;
};

#endif // MYCAMARA_H
