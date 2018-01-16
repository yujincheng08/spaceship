#include "mercury.h"
#include <QtDebug>

Mercury::Mercury(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_mercury.jpg");
  setSpecular("qrc:/assets/img/2k_mercury.jpg");
  setDiffuse("qrc:/assets/img/2k_mercury.jpg");
  setOriginPosition(QVector3D(870, 100, 0));
  setRadius(20);
  setAngle(120);
}
