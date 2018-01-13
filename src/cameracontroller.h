#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include <Qt3DExtras/QAbstractCameraController>

class Scene;
class SpaceShip;

class CameraController : public Qt3DExtras::QAbstractCameraController {
public:
  explicit CameraController(QNode *parent = nullptr, Scene *root = nullptr)
      : QAbstractCameraController(parent) {
    this->root = root;
    cursorLock = true;
  }

  virtual ~CameraController() final {}
  void setTraceTarget(SpaceShip *target);
  void setCursorLock(bool lock);
  bool getCursorLock();

private:
  void moveCamera(const QAbstractCameraController::InputState &state,
                  float dt) override;

public slots:
  void frameAction(float dt);

protected:
  CameraController(Qt3DExtras::QAbstractCameraControllerPrivate &dd,
                   QNode *parent = nullptr)
      : QAbstractCameraController(dd, parent) {}
  Scene *root;
  SpaceShip *target;
  bool cursorLock;
};

#endif // CAMERACONTROLLER_H
