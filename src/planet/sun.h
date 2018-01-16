#ifndef SUN_H
#define SUN_H

#include "planet.h"
#include <QEffect>
#include <QFilterKey>
#include <QRenderPass>
#include <QTechnique>

class Sun : public Planet {
public:
  using QEffect = Qt3DRender::QEffect;
  using QTechnique = Qt3DRender::QTechnique;
  using QRenderPass = Qt3DRender::QRenderPass;
  using QFilterKey = Qt3DRender::QFilterKey;

public:
  Sun(Scene *parent = nullptr);

private:
  QEffect *effect;
};

#endif // SUN_H
