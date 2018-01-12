#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include <Qt3DExtras/QAbstractCameraController>

class CameraController : public Qt3DExtras::QAbstractCameraController {
public:
  explicit CameraController(QNode *parent = nullptr)
      : QAbstractCameraController(parent) {}

  virtual ~CameraController() final {}

private:
  void moveCamera(const QAbstractCameraController::InputState &state,
                  float dt) override;

protected:
  CameraController(Qt3DExtras::QAbstractCameraControllerPrivate &dd,
                   QNode *parent = nullptr)
      : QAbstractCameraController(dd, parent) {}
};

#endif // CAMERACONTROLLER_H
