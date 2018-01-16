#include "earth.h"
#include <QtDebug>

Earth::Earth(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/earthnormal2k.jpg");
  setSpecular("qrc:/assets/img/earthspec2k.jpg");
  setDiffuse("qrc:/assets/img/earthmap2k.jpg");
  setOriginPosition(QVector3D(100, 100, 0));
  setRadius(60);
  setRotateSpeed(0.02);
  setAngle(0);
  setSpinSpeed(0.6);
}
