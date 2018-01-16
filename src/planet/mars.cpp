#include "mars.h"
#include <QtDebug>

Mars::Mars(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_mars.jpg");
  setSpecular("qrc:/assets/img/2k_mars.jpg");
  setDiffuse("qrc:/assets/img/2k_mars.jpg");
  setOriginPosition(QVector3D(-100, 100, 0));
  setRadius(30);
  setRotateSpeed(0.05);
  setAngle(30);
}
