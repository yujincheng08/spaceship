#ifndef QPLANETFRAMEGRAPH_H
#define QPLANETFRAMEGRAPH_H

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QClearBuffers>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QRenderPassFilter>
#include <Qt3DRender/QRenderSettings>
#include <Qt3DRender/QRenderSurfaceSelector>
#include <Qt3DRender/QRenderTarget>
#include <Qt3DRender/QRenderTargetOutput>
#include <Qt3DRender/QRenderTargetSelector>
#include <Qt3DRender/QTechniqueFilter>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureWrapMode>
#include <Qt3DRender/QViewport>

class PlanetFrameGraph : public Qt3DRender::QRenderSettings {
  using QCamera = Qt3DRender::QCamera;
  using QViewport = Qt3DRender::QViewport;
  using QCameraSelector = Qt3DRender::QCameraSelector;
  using QEntity = Qt3DCore::QEntity;
  using QRenderSurfaceSelector = Qt3DRender::QRenderSurfaceSelector;
  using QTechniqueFilter = Qt3DRender::QTechniqueFilter;
  using QRenderPassFilter = Qt3DRender::QRenderPassFilter;
  using QRenderTargetSelector = Qt3DRender::QRenderTargetSelector;
  using QRenderTarget = Qt3DRender::QRenderTarget;
  using QRenderTargetOutput = Qt3DRender::QRenderTargetOutput;
  using QClearBuffers = Qt3DRender::QClearBuffers;
  using QFilterKey = Qt3DRender::QFilterKey;
  using QTexture2D = Qt3DRender::QTexture2D;
  using QTextureWrapMode = Qt3DRender::QTextureWrapMode;

private:
  QViewport *viewport = new QViewport(this);
  QRenderSurfaceSelector *renderSurfaceSelector =
      new QRenderSurfaceSelector(viewport);
  QTechniqueFilter *techniqueFilter =
      new QTechniqueFilter(renderSurfaceSelector);
  QRenderPassFilter *renderPassShadowmapFilter =
      new QRenderPassFilter(techniqueFilter);
  QRenderTargetSelector *renderTargetSelector =
      new QRenderTargetSelector(renderPassShadowmapFilter);
  QRenderTarget *renderTarget = new QRenderTarget(renderTargetSelector);
  QRenderTargetOutput *renderTargetOutput =
      new QRenderTargetOutput(renderTarget);
  QClearBuffers *shadowmapClearBuffers =
      new QClearBuffers(renderTargetSelector);
  QRenderPassFilter *renderPassForwardFilter =
      new QRenderPassFilter(renderSurfaceSelector);
  QCameraSelector *viewCameraSelector =
      new QCameraSelector(shadowmapClearBuffers);
  QClearBuffers *forwardClearBuffers =
      new QClearBuffers(renderPassShadowmapFilter);
  QCameraSelector *lightCameraSelector =
      new QCameraSelector(forwardClearBuffers);
  QTexture2D *depthTexture = new QTexture2D;

public:
  PlanetFrameGraph(QNode *parent = nullptr);
  QEntity *viewCamera() { return viewCameraSelector->camera(); }
  QEntity *lightCamera() { return lightCameraSelector->camera(); }
  QTexture2D *getDepthTexture() { return depthTexture; }
};

#endif // QPLANETFRAMEGRAPH_H
