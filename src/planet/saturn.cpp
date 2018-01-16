#include "saturn.h"
#include <QtDebug>

Saturn::Saturn(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_saturn.jpg");
  setSpecular("qrc:/assets/img/2k_saturn.jpg");
  setDiffuse("qrc:/assets/img/2k_saturn.jpg");
  setOriginPosition(QVector3D(-800, 100, 0));
  setRadius(180);
  setRotateSpeed(0.015);
  setAngle(180);
  setSpinSpeed(0.1);
}
