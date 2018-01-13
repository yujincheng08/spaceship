#ifndef PLANET_H
#define PLANET_H

#include "component.h"
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
  Planet(QNode *parent = nullptr);
  virtual ~Planet() override {}
  void setRotateSpeed(qreal speed) { rotateSpeed = speed; }
  void setRadius(float radius) { mesh->setRadius(radius); }
  void setSlices(int slices) { mesh->setSlices(slices); }
  void setRings(int rings) { mesh->setRings(rings); }

protected:
  void setDiffuse(const QString &path) { diffuseImage->setSource(QUrl(path)); }
  void setSpecular(const QString &path) {
    specularImage->setSource(QUrl(path));
  }
  void setNormal(const QString &path) { normalImage->setSource(QUrl(path)); }
  void addMaterial() { addComponent(material); }

protected slots:
  void frameAction(float dt) override;

protected:
  qreal rotateSpeed = 0.0;
};

#endif // PLANET_H
