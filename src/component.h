#ifndef COMPONENT_H
#define COMPONENT_H

#include "bounding.h"
#include <QString>
#include <QVector>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QSceneLoader>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>

class Scene;

class Component : public Qt3DCore::QEntity {
public:
  using QMesh = Qt3DRender::QMesh;
  using QTransform = Qt3DCore::QTransform;
  using QMaterial = Qt3DRender::QMaterial;
  using QTextureMaterial = Qt3DExtras::QTextureMaterial;
  using QTextureImage = Qt3DRender::QTextureImage;
  using QTexture2D = Qt3DRender::QTexture2D;
  using QSceneLoader = Qt3DRender::QSceneLoader;
  using QPhongAlphaMaterial = Qt3DExtras::QPhongAlphaMaterial;
  using QPhongMaterial = Qt3DExtras::QPhongMaterial;

private:
  Scene *m_parentScene = nullptr;

public:
  void setPosition(QVector3D translation);
  virtual void explode() {}
  Scene *parentScene() const { return m_parentScene; }

protected:
  QTransform *transform = new QTransform;
  QQuaternion initDir;

public slots:
  virtual void frameAction(float dt) = 0;

public:
  Component(Scene *parent = nullptr);
  QVector3D getPostion() const;
  QVector3D getToward() const;
  QVector3D getUp() const;
  void setInitialDirection(const QVector3D &toward, const QVector3D &up);
  void setDirection(const QVector3D &toward, const QVector3D &up);
  virtual QList<BoundingBox> getBoundingBox() const {
    return QList<BoundingBox>();
  }
  virtual QList<BoundingSphere> getBoundingSphere() const {
    return QList<BoundingSphere>();
  }
  virtual ~Component() {}
};

#endif // COMPONENT_H
