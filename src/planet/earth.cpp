#include "earth.h"
#include <QtDebug>

Earth::Earth(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/earthnormal2k.jpg");
  setSpecular("qrc:/assets/img/earthspec2k.jpg");
  setDiffuse("qrc:/assets/img/earthmap2k.jpg");
  setPosition({100, 100, 0});
  setRadius(60);
  setRotateSpeed(2);
  setAngle(0);
  setSpinSpeed(60);
}
