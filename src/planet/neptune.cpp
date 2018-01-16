#include "neptune.h"
#include <QtDebug>

Neptune::Neptune(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_neptune.jpg");
  setSpecular("qrc:/assets/img/2k_neptune.jpg");
  setDiffuse("qrc:/assets/img/2k_neptune.jpg");
  setOriginPosition({-1000, 100, 0});
  setPosition(getOriginPosition());
  setRadius(150);
  setRotateSpeed(1);
  setAngle(90);
  setSpinSpeed(40);
}
