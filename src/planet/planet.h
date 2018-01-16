#ifndef PLANET_H
#define PLANET_H

#include "component.h"
#include "math.h"
#include <QPropertyAnimation>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QDiffuseSpecularMapMaterial>
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>
#include <Qt3DExtras/QSphereMesh>
#include <QtOpenGL>

class Planet : public Component {
public:
  using QSphereMesh = Qt3DExtras::QSphereMesh;
  using QNormalDiffuseSpecularMapMaterial =
      Qt3DExtras::QNormalDiffuseSpecularMapMaterial;
  using QDiffuseMapMaterial = Qt3DExtras::QDiffuseMapMaterial;
  using QDiffuseSpecularMapMaterial = Qt3DExtras::QDiffuseSpecularMapMaterial;

protected:
  QSphereMesh *mesh = new QSphereMesh;
  QNormalDiffuseSpecularMapMaterial *material =
      new QNormalDiffuseSpecularMapMaterial;
  QTextureImage *diffuseImage = new QTextureImage;
  QTextureImage *specularImage = new QTextureImage;
  QTextureImage *normalImage = new QTextureImage;
  QTexture2D *diffuseTexture = new QTexture2D;
  QTexture2D *specularTexture = new QTexture2D;
  QTexture2D *normalTexture = new QTexture2D;
  QPropertyAnimation *rotateAnimation = new QPropertyAnimation(this);

public:
  Planet(Scene *parent = nullptr);
  virtual ~Planet() override {}
  void setOrbitPlanet(Planet *orbitPlanet) { this->orbitPlanet = orbitPlanet; }
  Planet *getOrbitPlanet() const { return orbitPlanet; }
  void setRotateSpeed(qreal speed) { rotateSpeed = speed; }
  void setRadius(float radius) { mesh->setRadius(radius); }
  void setSlices(int slices) { mesh->setSlices(slices); }
  void setRings(int rings) { mesh->setRings(rings); }
  QVector3D getOriginPosition() { return this->originPosition; }
  void spin();
  virtual QList<BoundingSphere> getBoundingSphere() const override {
    return QList<BoundingSphere>()
           << BoundingSphere{getPostion(), mesh->radius()};
  }

protected:
  void setDiffuse(const QString &path) { diffuseImage->setSource(QUrl(path)); }
  void setSpecular(const QString &path) {
    specularImage->setSource(QUrl(path));
  }
  void setNormal(const QString &path) { normalImage->setSource(QUrl(path)); }
  void addMaterial() { addComponent(material); }
  void setOriginPosition(QVector3D pos) { originPosition = pos; }
  void setSpinSpeed(qreal speed) { spinSpeed = speed; }
  void setAngle(qreal angle) { currentAngle = angle; }
  qreal getRotateSpeed() { return rotateSpeed; }

public slots:
  void frameAction(float dt) override;

protected:
  qreal rotateSpeed = 0.0;
  qreal currentAngle = 0.0;
  qreal spinAngle = 0.0;
  qreal spinSpeed = 0.0;
  QVector3D originPosition;
  QVector3D orbitNormal = {0, 1, 0};
  void setOrbitNormal(const QVector3D &normal) {
    orbitNormal = normal;
    orbitNormal.normalize();
  }
  Planet *orbitPlanet = nullptr;
};

#endif // PLANET_H
