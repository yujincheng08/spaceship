#include "mercury.h"
#include <QtDebug>

Mercury::Mercury(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_mercury.jpg");
  setSpecular("qrc:/assets/img/2k_mercury.jpg");
  setDiffuse("qrc:/assets/img/2k_mercury.jpg");
  setOriginPosition({870, 100, 0});
  setPosition(getOriginPosition());
  setRotateSpeed(4);
  setRadius(20);
  setAngle(120);
  setSpinSpeed(20);
}
