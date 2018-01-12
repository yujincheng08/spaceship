#ifndef PLANET_H
#define PLANET_H

#include "component.h"
#include <GL/glut.h>
#include <QPropertyAnimation>
#include <Qt3DExtras/QSphereMesh>
#include <QtOpenGL>

class Planet : public Component {
public:
  using QSphereMesh = Qt3DExtras::QSphereMesh;

private:
  QSphereMesh *mesh = new QSphereMesh(this);
  QTransform *transform = new QTransform;
  QTextureImage *textureImage = new QTextureImage;
  QTexture2D *texture = new QTexture2D;
  QTextureMaterial *material = new QTextureMaterial;
  QPropertyAnimation *rotateAnimation = new QPropertyAnimation(this);

public:
  Planet(QNode *parent = nullptr);
  ~Planet();
  void setRotateSpeed(GLfloat speed) { rotateSpeed = speed; }
  void setRadius(float radius) {
    if (radius > 0)
      mesh->setRadius(radius);
  }
  void setSlice(int slices) {
    if (slices > 0)
      mesh->setSlices(slices);
  }

protected:
  float rotateSpeed;
};

#endif // PLANET_H
