#ifndef PLANETEFFECT_H
#define PLANETEFFECT_H

#include "planetlight.h"
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QTexture>

class PlanetEffect : public Qt3DRender::QEffect {
public:
  using QTexture2D = Qt3DRender::QTexture2D;
  using QParameter = Qt3DRender::QParameter;
  using QRenderPass = Qt3DRender::QRenderPass;
  using QTechnique = Qt3DRender::QTechnique;
  using QFilterKey = Qt3DRender::QFilterKey;
  using QShaderProgram = Qt3DRender::QShaderProgram;
  using QGraphicsApiFilter = Qt3DRender::QGraphicsApiFilter;

private:
  QFilterKey *eskey = new QFilterKey(this);
  QFilterKey *glkey = new QFilterKey(this);
  QFilterKey *forwardkey = new QFilterKey(this);
  QRenderPass *glpass = new QRenderPass(this);
  QRenderPass *espass = new QRenderPass(this);
  QTechnique *gltech = new QTechnique(this);
  QTechnique *estech = new QTechnique(this);
  QTechnique *glestech = new QTechnique(this);
  QParameter *lightViewParameter = new QParameter(this);
  QParameter *lightPositionParameter = new QParameter(this);
  QParameter *lightIntensityParameter = new QParameter(this);
  QShaderProgram *glShaderProgram = new QShaderProgram(this);
  QShaderProgram *esShaderProgram = new QShaderProgram(this);

public:
  PlanetEffect(QNode *parent = nullptr);
  void setPlanetLight(PlanetLight *light) {
    lightViewParameter->setValue(light->getLightViewProjection());
    lightIntensityParameter->setValue(light->getLightIntensity());
    lightPositionParameter->setValue(light->getLightPosition());
  }
};

#endif // PLANETEFFECT_H
