#include "moon.h"
#include <QtDebug>

Moon::Moon(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_moon.jpg");
  setSpecular("qrc:/assets/img/2k_moon.jpg");
  setDiffuse("qrc:/assets/img/2k_moon.jpg");
  setOriginPosition({20, 100, 0});
  setPosition(getOriginPosition());
  setRadius(17);
  setRotateSpeed(100);
  setAngle(0);
  setSpinSpeed(20);
}
