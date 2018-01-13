#include "planet.h"

Planet::Planet(QNode *parent) : Component(parent) {
  setRings(64);
  setSlices(64);
  diffuseTexture->addTextureImage(diffuseImage);
  normalTexture->addTextureImage(normalImage);
  specularTexture->addTextureImage(specularImage);
  material->setDiffuse(diffuseTexture);
  material->setNormal(normalTexture);
  material->setSpecular(specularTexture);
  material->setAmbient(QColor::fromRgb(22, 22, 22));
  material->setShininess(50.0f);
  addComponent(mesh);
  addComponent(material);
}

void Planet::frameAction(float dt) {}

// void Planet::gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks) {
//  GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat)iStacks;
//  GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat)iSlices;
//  GLfloat ds = 1.0f / (GLfloat)iSlices;
//  GLfloat dt = 1.0f / (GLfloat)iStacks;
//  GLfloat t = 1.0f;
//  GLfloat s = 0.0f;
//  GLint i, j;

//  for (i = 0; i < iStacks; i++) {
//    GLfloat rho = (GLfloat)i * drho;
//    GLfloat srho = (GLfloat)(sin(rho));
//    GLfloat crho = (GLfloat)(cos(rho));
//    GLfloat srhodrho = (GLfloat)(sin(rho + drho));
//    GLfloat crhodrho = (GLfloat)(cos(rho + drho));

//    glBegin(GL_TRIANGLE_STRIP);
//    s = 0.0f;
//    for (j = 0; j <= iSlices; j++) {
//      GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
//      GLfloat stheta = (GLfloat)(-sin(theta));
//      GLfloat ctheta = (GLfloat)(cos(theta));

//      GLfloat x = stheta * srho;
//      GLfloat y = ctheta * srho;
//      GLfloat z = crho;

//      glTexCoord2f(s, t);
//      glNormal3f(x, y, z);
//      glVertex3f(x * fRadius, y * fRadius, z * fRadius);

//      x = stheta * srhodrho;
//      y = ctheta * srhodrho;
//      z = crhodrho;
//      glTexCoord2f(s, t - dt);
//      s += ds;
//      glNormal3f(x, y, z);
//      glVertex3f(x * fRadius, y * fRadius, z * fRadius);
//    }
//    glEnd();

//    t -= dt;
//  }
//}

// void Planet::repaint() {

//  glBindTexture(GL_TEXTURE_2D, earth->texID);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, earth->width, earth->height,
//  GL_RGB,
//                    GL_UNSIGNED_BYTE, earth->data);

//  qDebug() << "width=" << earth->width << " height=" << earth->height << endl;
//  qDebug() << "ID=" << earth->texID << endl;
//  qDebug() << "data=" << *(earth->data) << endl;

//  glPushMatrix();
//  glTranslated(xPos, yPos, zPos);
//  glRotatef(RotateSpeed, 0.0, 1.0, 0.0); //自转
//  glRotatef(90, -1, 0, 0);

//  glPopMatrix();
//}
