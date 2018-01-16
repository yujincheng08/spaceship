#include "planeteffect.h"

PlanetEffect::PlanetEffect(QNode *parent) : QEffect(parent) {
  lightViewParameter->setName("lightViewProjection");
  lightPositionParameter->setName("lightPosition");
  lightIntensityParameter->setName("lightIntensity");
  eskey->setName("name");
  eskey->setValue("ES2");
  glkey->setName("name");
  glkey->setValue("Desktop");
  forwardkey->setName("name");
  forwardkey->setValue("forward");
  glpass->addFilterKey(forwardkey);
  glShaderProgram->setVertexShaderCode(
      QShaderProgram::loadSource(QUrl("qrc:/shaders/gl3/planetD.vert")));
  glShaderProgram->setFragmentShaderCode(
      QShaderProgram::loadSource(QUrl("qrc:/shaders/gl3/planetD.frag")));
  glpass->setShaderProgram(glShaderProgram);
  espass->addFilterKey(forwardkey);
  esShaderProgram->setVertexShaderCode(
      QShaderProgram::loadSource(QUrl("qrc:/shaders/es2/planetD.vert")));
  esShaderProgram->setFragmentShaderCode(
      QShaderProgram::loadSource(QUrl("qrc:/shaders/es2/planetD.frag")));
  espass->setShaderProgram(esShaderProgram);
  gltech->graphicsApiFilter()->setApi(QGraphicsApiFilter::OpenGL);
  gltech->graphicsApiFilter()->setProfile(QGraphicsApiFilter::CoreProfile);
  gltech->graphicsApiFilter()->setMajorVersion(3);
  gltech->graphicsApiFilter()->setMinorVersion(2);
  gltech->addFilterKey(glkey);
  gltech->addRenderPass(glpass);
  estech->graphicsApiFilter()->setApi(QGraphicsApiFilter::OpenGL);
  estech->graphicsApiFilter()->setMajorVersion(2);
  estech->addFilterKey(eskey);
  estech->addRenderPass(espass);
  glestech->graphicsApiFilter()->setApi(QGraphicsApiFilter::OpenGLES);
  glestech->graphicsApiFilter()->setMajorVersion(2);
  glestech->graphicsApiFilter()->setMinorVersion(0);
  glestech->addFilterKey(eskey);
  glestech->addRenderPass(espass);
  addParameter(lightViewParameter);
  addParameter(lightPositionParameter);
  addParameter(lightIntensityParameter);
  addTechnique(gltech);
  addTechnique(estech);
  addTechnique(glestech);
  qDebug() << parameters().size() << techniques().size();
}
