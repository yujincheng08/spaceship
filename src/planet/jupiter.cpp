#include "jupiter.h"
#include <QtDebug>

Jupiter::Jupiter(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_jupiter.jpg");
  setSpecular("qrc:/assets/img/2k_jupiter.jpg");
  setDiffuse("qrc:/assets/img/2k_jupiter.jpg");
  setOriginPosition({-500, 100, 0});
  setPosition(getOriginPosition());
  setRadius(200);
  setRotateSpeed(6);
  setAngle(0);
  setSpinSpeed(20);
}
