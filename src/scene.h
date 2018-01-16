#ifndef SCENE_H
#define SCENE_H

#include "directionallight.h"
#include "pointlight.h"
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DInput/QInputAspect>
#include <Qt3DLogic/QFrameAction>
#include <cameracontroller.h>
#include <planet/earth.h>
#include <planet/jupiter.h>
#include <planet/mars.h>
#include <planet/mercury.h>
#include <planet/moon.h>
#include <planet/neptune.h>
#include <planet/saturn.h>
#include <planet/sun.h>
#include <planet/uranus.h>
#include <planet/venus.h>

#include <spaceship.h>
#include <starfield.h>

class Scene : public Qt3DExtras::Qt3DWindow {
public:
  using QEntity = Qt3DCore::QEntity;
  using QDirectionalLight = Qt3DRender::QDirectionalLight;
  using QFrameAction = Qt3DLogic::QFrameAction;

private:
  QEntity *root = new QEntity();
  SpaceShip *spaceship = new SpaceShip(root);
  Earth *earth = new Earth(root);
  Sun *sun = new Sun(root);
  Moon *moon = new Moon(root);
  Mercury *mercury = new Mercury(root);
  Venus *venus = new Venus(root);
  Mars *mars = new Mars(root);
  Jupiter *jupiter = new Jupiter(root);
  Saturn *saturn = new Saturn(root);
  Neptune *neptune = new Neptune(root);
  Uranus *uranus = new Uranus(root);

  CameraController *controller = new CameraController(root, this);
  PointLight *light = new PointLight(root);
  PointLight *light_sun = new PointLight(root);
  QFrameAction *frame = new QFrameAction(root);
  Starfield *starfield = new Starfield(root);

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
