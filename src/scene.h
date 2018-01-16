#ifndef SCENE_H
#define SCENE_H

#include "directionallight.h"
#include "laserbullet.h"
#include "overlaywidget.h"
#include "pointlight.h"
#include <QNode>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DInput/QInputAspect>
#include <Qt3DLogic/QFrameAction>
#include <cameracontroller.h>
#include <planet/earth.h>
#include <spaceship.h>
#include <starfield.h>

class OverlayWidget;

class Scene : public Qt3DExtras::Qt3DWindow {
public:
  using QNode = Qt3DCore::QNode;
  using QEntity = Qt3DCore::QEntity;
  using QDirectionalLight = Qt3DRender::QDirectionalLight;

private:
  QEntity *root = new QEntity();

  SpaceShip *spaceship = new SpaceShip(root, this);
  Earth *earth = new Earth(root);

  CameraController *controller = new CameraController(root, this);
  // PointLight *light = new PointLight(root);
  QFrameAction *frame = new QFrameAction(root);
  Starfield *starfield = new Starfield(root);
  OverlayWidget *ow;

  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *e) override;

public:
  Scene(QScreen *parent = nullptr);
  QEntity *getRoot() { return root; }
  virtual ~Scene() final { delete root; }

  SpaceShip *getSpaceship() { return spaceship; }
  void addLaserBullet(const QVector3D &pos, const QVector3D &velocity);
  void addLaserBullet(const QVector3D &pos, const float &speed);

  void spaceshipExplode(SpaceShip *spaceship);

  void removeLaserBullet(LaserBullet *bullet);

  void addObserver(OverlayWidget *ow) {
    this->ow = ow;
    connect(frame, &QFrameAction::triggered, ow, &OverlayWidget::frameAction);
  }

private:
public slots:
  void frameAction(float dt) { Q_UNUSED(dt) }
};

#endif // SCENE_H
