#ifndef SCENE_H
#define SCENE_H

#include "directionallight.h"
#include "pointlight.h"
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DInput/QInputAspect>
#include <Qt3DLogic/QFrameAction>
#include <cameracontroller.h>
#include <planet.h>
#include <spaceship.h>

class Scene : public Qt3DExtras::Qt3DWindow {
public:
  using QEntity = Qt3DCore::QEntity;
  using QDirectionalLight = Qt3DRender::QDirectionalLight;
  using QFrameAction = Qt3DLogic::QFrameAction;

private:
  QEntity *root = new QEntity();
  SpaceShip *spaceship = new SpaceShip(root);
  Planet *earth = new Planet(root);
  Planet *sun = new Planet(root);
  CameraController *controller = new CameraController(root, this);
  PointLight *light = new PointLight(root);
  QFrameAction *frame = new QFrameAction(root);

  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;

public:
  Scene(QScreen *parent = nullptr);
  virtual ~Scene() final { delete root; }

  SpaceShip *getSpaceship() { return spaceship; }

private:
  void initCamera();
  void initPlanets();
  void initSpaceship();
  void initLight();
  void initFrame();

private slots:
  void frameAction(float dt);
};

#endif // SCENE_H
