#ifndef SCENE_H
#define SCENE_H

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DInput/QInputAspect>
#include <cameracontroller.h>
#include <planet.h>
#include <spaceship.h>
class Scene : public Qt3DExtras::Qt3DWindow {
public:
  using QEntity = Qt3DCore::QEntity;

private:
  QEntity *root = new QEntity();
  SpaceShip *spaceShip = new SpaceShip(root);
  Planet *planet = new Planet(root);
  CameraController *controller = new CameraController(root);

public:
  Scene(QScreen *parent = nullptr);
  virtual ~Scene() final { delete root; }

private:
  void initCamera();
};

#endif // SCENE_H
