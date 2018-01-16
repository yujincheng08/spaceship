#include "moon.h"
#include <QtDebug>

Moon::Moon(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_moon.jpg");
  setSpecular("qrc:/assets/img/2k_moon.jpg");
  setDiffuse("qrc:/assets/img/2k_moon.jpg");
  setOriginPosition(QVector3D(10, 100, 0));
  setRadius(17);
  setRotateSpeed(1);
  setAngle(0);
  setSpinSpeed(0.2);
}
