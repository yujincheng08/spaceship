#include "sun.h"
#include <QtDebug>

Sun::Sun(Scene *parent) : Planet(parent) {
  QShaderProgram *s1 = new QShaderProgram, *s2 = new QShaderProgram;
  s1->setVertexShaderCode(
      QShaderProgram::loadSource(QUrl("qrc:/shaders/gl3/sun.vert")));
  s1->setFragmentShaderCode(
      QShaderProgram::loadSource(QUrl("qrc:/shaders/gl3/sun.frag")));
  s2->setVertexShaderCode(
      QShaderProgram::loadSource(QUrl("qrc:/shaders/es2/sun.vert")));
  s2->setFragmentShaderCode(
      QShaderProgram::loadSource(QUrl("qrc:/shaders/es2/sun.frag")));

  QFilterKey *k1 = new QFilterKey, *k2 = new QFilterKey, *k3 = new QFilterKey;
  k1->setValue(QVariant("Desktop"));
  k1->setName("name");
  k2->setValue("forward");
  k2->setName("pass");
  k3->setValue("ES2");
  k3->setName("name");

  QRenderPass *p1 = new QRenderPass, *p2 = new QRenderPass;
  p1->addFilterKey(k2);
  p1->setShaderProgram(s1);
  p2->addFilterKey(k2);
  p2->setShaderProgram(s2);

  QTechnique *t1 = new QTechnique, *t2 = new QTechnique, *t3 = new QTechnique;
  t1->addRenderPass(p1);
  t1->addFilterKey(k1);
  t1->graphicsApiFilter()->setApi(QGraphicsApiFilter::OpenGL);
  t1->graphicsApiFilter()->setProfile(QGraphicsApiFilter::CoreProfile);
  t1->graphicsApiFilter()->setMajorVersion(3);
  t1->graphicsApiFilter()->setMinorVersion(2);
  t2->addRenderPass(p2);
  t2->addFilterKey(k3);
  t2->graphicsApiFilter()->setApi(QGraphicsApiFilter::OpenGL);
  t2->graphicsApiFilter()->setMajorVersion(2);
  t3->addRenderPass(p2);
  t3->addFilterKey(k3);
  t3->graphicsApiFilter()->setApi(QGraphicsApiFilter::OpenGLES);
  t3->graphicsApiFilter()->setMajorVersion(2);
  t3->graphicsApiFilter()->setMinorVersion(0);

  effect = new QEffect;
  effect->addTechnique(t1);
  effect->addTechnique(t2);
  effect->addTechnique(t3);

  //  material->setEffect(effect);
  material->setAmbient(QColor(255, 255, 255));

  setNormal("qrc:/assets/img/2k_sun.jpg");
  setSpecular("qrc:/assets/img/2k_sun.jpg");
  setDiffuse("qrc:/assets/img/2k_sun.jpg");
  setOriginPosition({1500, 100, 0});
  setPosition(getOriginPosition());
  setRadius(600);
}
