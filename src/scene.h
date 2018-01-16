#ifndef SCENE_H
#define SCENE_H

#include "directionallight.h"
#include "laserbullet.h"
#include "overlaywidget.h"
#include "pointlight.h"
#include <QNode>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>

class Scene : public Qt3DExtras::Qt3DWindow {
public:
  using QNode = Qt3DCore::QNode;
  using QEntity = Qt3DCore::QEntity;
  using QDirectionalLight = Qt3DRender::QDirectionalLight;

private:
  QEntity *root = new QEntity();

public:
  Scene(QScreen *parent = nullptr);
  QEntity *getRoot() { return root; }
  virtual ~Scene() final { delete root; }

private:
public slots:
  void frameAction(float dt) { Q_UNUSED(dt) }
};

#endif // SCENE_H
