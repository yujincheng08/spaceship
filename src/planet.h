#ifndef PLANET_H
#define PLANET_H

#include "component.h"
#include "vector.h"
#include <QtOpenGL>
#include <gl/glut.h>

class planet : public Component {
public:
  planet();
  ~planet();
  void setRotateSpeed(GLfloat speed);
  void setTexID(unsigned int texID);
  void repaint();
  void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks);

protected:
  GLfloat radius;
  GLfloat RotateSpeed;
  unsigned int texID;
};

#endif // PLANET_H
