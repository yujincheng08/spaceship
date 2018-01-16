#include "sun.h"
#include <QtDebug>

Sun::Sun(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_sun.jpg");
  setSpecular("qrc:/assets/img/2k_sun.jpg");
  setDiffuse("qrc:/assets/img/2k_sun.jpg");
  setOriginPosition(QVector3D(1500, 100, 0));
  setRadius(600);
}
