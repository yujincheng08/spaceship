#include "earth.h"
#include <QtDebug>

Earth::Earth(QNode *parent) : Planet(parent) {
  setNormal("qrc:/assets/img/earthnormal2k.jpg");
  setSpecular("qrc:/assets/img/earthspec2k.jpg");
  setDiffuse("qrc:/assets/img/earthmap2k.jpg");
}
