#ifndef SCENE_H
#define SCENE_H

#include "directionallight.h"
#include "laserbullet.h"
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

class Scene : public Qt3DExtras::Qt3DWindow {
public:
  using QNode = Qt3DCore::QNode;
  using QEntity = Qt3DCore::QEntity;
  using QDirectionalLight = Qt3DRender::QDirectionalLight;
  using QFrameAction = Qt3DLogic::QFrameAction;

private:
  QEntity *root = new QEntity();

  SpaceShip *spaceship = new SpaceShip(root, this);
  Earth *earth = new Earth(root);

  CameraController *controller = new CameraController(root, this);
  // PointLight *light = new PointLight(root);
  QFrameAction *frame = new QFrameAction(root);
  Starfield *starfield = new Starfield(root);

  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *e) override;

public:
  Scene(QScreen *parent = nullptr);
  virtual ~Scene() final { delete root; }

  SpaceShip *getSpaceship() { return spaceship; }
  void addLaserBullet(const QVector3D &pos, const QVector3D &velocity);
  void addLaserBullet(const QVector3D &pos, const float &speed);

  void spaceshipExplode(SpaceShip *spaceship);

  void removeLaserBullet(LaserBullet *bullet);

private:
  void initCamera();
  void initPlanets();
  void initSpaceship();
  void initLight();
  void initFrame();

  void gameOver();
private slots:
  void frameAction(float dt);
};

#endif // SCENE_H
