#include "planetframegraph.h"
#include <QRectF>

PlanetFrameGraph::PlanetFrameGraph(QNode *parent) : QRenderSettings(parent) {
  setActiveFrameGraph(viewport);
  viewport->setNormalizedRect(QRectF{0.0f, 0.0f, 1.0f, 1.0f});
  QFilterKey *key = new QFilterKey;
  key->setName("name");
  key->setValue("Desktop");
  techniqueFilter->addMatch(key);
  key = new QFilterKey;
  key->setName("pass");
  key->setName("shadowmap");
  renderPassShadowmapFilter->addMatch(key);
  renderTargetSelector->setTarget(renderTarget);
  renderTarget->addOutput(renderTargetOutput);
  renderTargetOutput->setObjectName("depth");
  renderTargetOutput->setAttachmentPoint(QRenderTargetOutput::Depth);
  renderTargetOutput->setTexture(depthTexture);
  depthTexture->setWidth(1920);
  depthTexture->setWidth(1080);
  depthTexture->setFormat(QTexture2D::D24);
  depthTexture->setGenerateMipMaps(false);
  depthTexture->setMagnificationFilter(QTexture2D::Linear);
  depthTexture->setMinificationFilter(QTexture2D::Linear);
  depthTexture->wrapMode()->setX(QTextureWrapMode::ClampToEdge);
  depthTexture->wrapMode()->setY(QTextureWrapMode::ClampToEdge);
  depthTexture->setComparisonFunction(QTexture2D::CompareLessEqual);
  depthTexture->setComparisonMode(QTexture2D::CompareRefToTexture);
  shadowmapClearBuffers->setBuffers(QClearBuffers::DepthBuffer);
  shadowmapClearBuffers->setClearColor(QColor::fromRgbF(0.0, 0.0, 0.0));
  key = new QFilterKey;
  key->setName("pass");
  key->setName("forward");
  renderPassForwardFilter->addMatch(key);
  forwardClearBuffers->setBuffers(QClearBuffers::ColorDepthBuffer);
}
