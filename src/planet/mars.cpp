#include "mars.h"
#include <QtDebug>

Mars::Mars(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_mars.jpg");
  setSpecular("qrc:/assets/img/2k_mars.jpg");
  setDiffuse("qrc:/assets/img/2k_mars.jpg");
  setOriginPosition({-100, 100, 0});
  setPosition(getOriginPosition());
  setRadius(30);
  setRotateSpeed(5);
  setAngle(240);
  setSpinSpeed(60);
}
