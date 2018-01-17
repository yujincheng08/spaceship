#include "saturn.h"
#include <QtDebug>

Saturn::Saturn(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_saturn.jpg");
  setSpecular("qrc:/assets/img/2k_saturn.jpg");
  setDiffuse("qrc:/assets/img/2k_saturn.jpg");
  setOriginPosition({-800, 100, 0});
  setPosition(getOriginPosition());
  setRadius(180);
  setRotateSpeed(15);
  setAngle(180);
  setSpinSpeed(10);
}
