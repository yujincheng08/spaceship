#include "scene.h"
#include <Qt3DRender/QCamera>
Scene::Scene(QScreen *parent) : Qt3DExtras::Qt3DWindow(parent) {
  setRootEntity(root);
  initCamera();
}

void Scene::initCamera() {
  camera()->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f,
                                             1000.0f);
  camera()->setPosition(QVector3D(0, 0, 1.0f));
  camera()->setViewCenter(QVector3D(0, 0, 0));
  controller->setLinearSpeed(50.0f);
  controller->setLookSpeed(180.0f);
  controller->setCamera(camera());
}
