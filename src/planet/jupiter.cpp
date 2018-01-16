#include "jupiter.h"
#include <QtDebug>

Jupiter::Jupiter(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_jupiter.jpg");
  setSpecular("qrc:/assets/img/2k_jupiter.jpg");
  setDiffuse("qrc:/assets/img/2k_jupiter.jpg");
  setOriginPosition(QVector3D(-500, 100, 0));
  setRadius(200);
  setRotateSpeed(0.06);
  setAngle(0);
}
