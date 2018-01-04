#include "planet.h"

planet::planet() { setRotateSpeed(0); }

planet::~planet() {}

void planet::setRotateSpeed(GLfloat speed) { RotateSpeed = speed; }

void planet::setTexID(unsigned int id) { texID = id; }

void planet::gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks) {
  GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat)iStacks;
  GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat)iSlices;
  GLfloat ds = 1.0f / (GLfloat)iSlices;
  GLfloat dt = 1.0f / (GLfloat)iStacks;
  GLfloat t = 1.0f;
  GLfloat s = 0.0f;
  GLint i, j;

  for (i = 0; i < iStacks; i++) {
    GLfloat rho = (GLfloat)i * drho;
    GLfloat srho = (GLfloat)(sin(rho));
    GLfloat crho = (GLfloat)(cos(rho));
    GLfloat srhodrho = (GLfloat)(sin(rho + drho));
    GLfloat crhodrho = (GLfloat)(cos(rho + drho));

    glBegin(GL_TRIANGLE_STRIP);
    s = 0.0f;
    for (j = 0; j <= iSlices; j++) {
      GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
      GLfloat stheta = (GLfloat)(-sin(theta));
      GLfloat ctheta = (GLfloat)(cos(theta));

      GLfloat x = stheta * srho;
      GLfloat y = ctheta * srho;
      GLfloat z = crho;

      glTexCoord2f(s, t);
      glNormal3f(x, y, z);
      glVertex3f(x * fRadius, y * fRadius, z * fRadius);

      x = stheta * srhodrho;
      y = ctheta * srhodrho;
      z = crhodrho;
      glTexCoord2f(s, t - dt);
      s += ds;
      glNormal3f(x, y, z);
      glVertex3f(x * fRadius, y * fRadius, z * fRadius);
    }
    glEnd();

    t -= dt;
  }
}

void planet::repaint() {
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texID);
  glRotatef(RotateSpeed, 0.0, 1.0, 0.0); //自转
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  // glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glRotatef(90, -1, 0, 0);

  glDisable(GL_LIGHTING);
  gltDrawSphere(radius, xPos, yPos); //绘制
  glEnable(GL_LIGHTING);
  // glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  glPopMatrix();
}
