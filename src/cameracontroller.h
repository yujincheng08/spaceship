#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include "component.h"
#include <QVector3D>
#include <Qt3DRender/QCamera>
class Scene;
class SpaceShip;

class CameraController : public Component {
public:
  using QCamera = Qt3DRender::QCamera;
  explicit CameraController(QNode *parent = nullptr, Scene *root = nullptr)
      : Component(parent) {
    this->root = root;
    cursorLock = true;
    posTrans = QVector3D(0, 4, -20);
    ctrTrans = QVector3D(0, 4, 0);
  }

  virtual ~CameraController() final {}
  void setTraceTarget(Component *target) { this->target = target; }
  void setCursorLock(bool lock);
  bool getCursorLock() { return cursorLock; }
  void setCamera(QCamera *camera) { this->camera = camera; }
  QVector3D getToward();

private:
  QVector3D TransPosition(const QVector3D &up, const QVector3D &twd,
                          const QVector3D &pos, const QVector3D &trans);
  QVector3D getTransPosition(const QVector3D &up, const QVector3D &twd,
                             const QVector3D &pos, const QVector3D &trans);

public slots:
  void frameAction(float dt);

protected:
  Scene *root = nullptr;
  Component *target = nullptr;
  QCamera *camera = nullptr;
  bool cursorLock = true;
  bool isActived = true;

  QVector3D posTrans, ctrTrans;
};

#endif // CAMERACONTROLLER_H
