#include "uranus.h"
#include <QtDebug>

Uranus::Uranus(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_uranus.jpg");
  setSpecular("qrc:/assets/img/2k_uranus.jpg");
  setDiffuse("qrc:/assets/img/2k_uranus.jpg");
  setOriginPosition(QVector3D(-1200, 100, 0));
  setRadius(150);
  setRotateSpeed(0.04);
  setAngle(150);
  setSpinSpeed(0.3);
}
