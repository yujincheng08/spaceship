#ifndef PLANETLIGHT_H
#define PLANETLIGHT_H

#include <QMatrix4x4>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>

class PlanetLight : public Qt3DCore::QEntity {
public:
  using QCamera = Qt3DRender::QCamera;
  using QCameraLens = Qt3DRender::QCameraLens;

private:
  QCamera *lightCamera = new QCamera(this);
  QVector3D lightIntensity = QVector3D{1.0f, 1.0f, 1.0f};

public:
  PlanetLight(QNode *parent = nullptr);
  QMatrix4x4 getLightViewProjection() const {
    return lightCamera->projectionMatrix() * lightCamera->viewMatrix();
  }
  void setLightPosition(const QVector3D &pos) { lightCamera->setPosition(pos); }
  QVector3D getLightPosition() { return lightCamera->position(); }
  QVector3D getLightIntensity() { return lightIntensity; }
  void setLightIntensity(const QVector3D intensity) {
    lightIntensity = intensity;
  }
  void setRatio(float ratio) { lightCamera->setAspectRatio(ratio); }
  void setNear(float near) { lightCamera->setNearPlane(near); }
};

#endif // PLANETLIGHT_H
