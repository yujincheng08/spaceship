#include "sun.h"
#include <QtDebug>

Sun::Sun(Scene *parent) : Planet(parent) {
  QFilterKey *k1 = new QFilterKey, *k2 = new QFilterKey, *k3 = new QFilterKey;

  QRenderPass *p1 = new QRenderPass;
  p1->addFilterKey(k1);

  QTechnique *t1 = new QTechnique;
  t1->addRenderPass(p1);
  t1->addFilterKey(k1);

  effect = new QEffect;
  effect->addTechnique(t1);

  material->setEffect(effect);

  setNormal("qrc:/assets/img/2k_sun.jpg");
  setSpecular("qrc:/assets/img/2k_sun.jpg");
  setDiffuse("qrc:/assets/img/2k_sun.jpg");
  setOriginPosition(QVector3D(1500, 100, 0));
  setRadius(600);
}
