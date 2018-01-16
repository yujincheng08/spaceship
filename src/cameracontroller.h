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
  explicit CameraController(Scene *parent = nullptr) : Component(parent) {
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
  void zoom(const bool &direction);
  void release() {
    isRelease = true;
    target = nullptr;
  }

private:
  QVector3D TransPosition(const QVector3D &up, const QVector3D &twd,
                          const QVector3D &pos, const QVector3D &trans);
  QVector3D getTransPosition(const QVector3D &up, const QVector3D &twd,
                             const QVector3D &pos, const QVector3D &trans);

public slots:
  void frameAction(float dt);

protected:
  Component *target = nullptr;
  QCamera *camera = nullptr;
  bool cursorLock = true;
  bool isActived = true;
  bool isRelease = false;

  QVector3D posTrans, ctrTrans;
};

#endif // CAMERACONTROLLER_H
