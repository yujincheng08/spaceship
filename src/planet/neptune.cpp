#include "neptune.h"
#include <QtDebug>

Neptune::Neptune(QNode *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_neptune.jpg");
  setSpecular("qrc:/assets/img/2k_neptune.jpg");
  setDiffuse("qrc:/assets/img/2k_neptune.jpg");
  setOriginPosition(QVector3D(-1000, 100, 0));
  setRadius(150);
  setRotateSpeed(0.01);
  setAngle(90);
}
