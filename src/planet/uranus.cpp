#include "uranus.h"
#include <QtDebug>

Uranus::Uranus(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_uranus.jpg");
  setSpecular("qrc:/assets/img/2k_uranus.jpg");
  setDiffuse("qrc:/assets/img/2k_uranus.jpg");
  setOriginPosition({-1200, 100, 0});
  setPosition(getOriginPosition());
  setRadius(150);
  setRotateSpeed(4);
  setAngle(270);
  setSpinSpeed(30);
}
