#include "venus.h"
#include <QtDebug>

Venus::Venus(Scene *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/2k_venus_surface.jpg");
  setSpecular("qrc:/assets/img/2k_venus_surface.jpg");
  setDiffuse("qrc:/assets/img/2k_venus_surface.jpg");
  setOriginPosition({400, 100, 0});
  setPosition(getOriginPosition());
  setRadius(60);
  setRotateSpeed(7);
  setAngle(210);
  setSpinSpeed(50);
}
