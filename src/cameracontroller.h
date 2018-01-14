#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include <QVector3D>
#include <Qt3DExtras/QAbstractCameraController>

class Scene;
class SpaceShip;

class CameraController : public Qt3DExtras::QAbstractCameraController {
public:
  explicit CameraController(QNode *parent = nullptr, Scene *root = nullptr)
      : QAbstractCameraController(parent) {
    this->root = root;
    cursorLock = true;
    posTrans = QVector3D(0, 4, -20);
    ctrTrans = QVector3D(0, 4, 0);
  }

  virtual ~CameraController() final {}
  void setTraceTarget(SpaceShip *target);
  void setCursorLock(bool lock);
  bool getCursorLock();
  QVector3D getToward();

private:
  void moveCamera(const QAbstractCameraController::InputState &,
                  float) override {}
  QVector3D TransPosition(const QVector3D &up, const QVector3D &twd,
                          const QVector3D &pos, const QVector3D &trans);
  QVector3D getTransPosition(const QVector3D &up, const QVector3D &twd,
                             const QVector3D &pos, const QVector3D &trans);

public slots:
  void frameAction(float dt);

protected:
  CameraController(Qt3DExtras::QAbstractCameraControllerPrivate &dd,
                   QNode *parent = nullptr)
      : QAbstractCameraController(dd, parent) {}
  Scene *root;
  SpaceShip *target;
  bool cursorLock;

  QVector3D posTrans, ctrTrans;
};

#endif // CAMERACONTROLLER_H
