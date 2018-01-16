#include "venus.h"
#include <QtDebug>

Venus::Venus(QNode *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_venus_surface.jpg");
  setSpecular("qrc:/assets/img/2k_venus_surface.jpg");
  setDiffuse("qrc:/assets/img/2k_venus_surface.jpg");
  setOriginPosition(QVector3D(400, 100, 0));
  setRadius(60);
  setRotateSpeed(0.07);
  setAngle(210);
}
