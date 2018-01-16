#ifndef LASERBULLET_H
#define LASERBULLET_H

#include "component.h"
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>

class Scene;

class LaserBullet : public Component {
public:
  using QConeMesh = Qt3DExtras::QConeMesh;
  using QNormalDiffuseSpecularMapMaterial =
      Qt3DExtras::QNormalDiffuseSpecularMapMaterial;

public:
  LaserBullet(const QVector3D &startPos, const QVector3D &velocity,
              Scene *parent = nullptr);
  virtual ~LaserBullet() override {}

protected:
  QConeMesh *mesh = new QConeMesh;
  QPhongAlphaMaterial *material = new QPhongAlphaMaterial;

protected slots:
  void frameAction(float dt) override;

private:
  Scene *root;
  QColor color;
  float length;
  QVector3D velocity;
  float existTime;
};

#endif // LASERBULLET_H
