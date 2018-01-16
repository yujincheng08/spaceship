#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "boundingbox.h"
#include "overlaywidget.h"
#include "scene.h"
#include <QObject>
#include <QTime>
#include <Qt3DInput/QInputAspect>
#include <Qt3DInput>
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

class Controller : public QObject {
  Q_OBJECT
public:
  using QFrameAction = Qt3DLogic::QFrameAction;
  using QMouseDevice = Qt3DInput::QMouseDevice;
  using QKeyboardDevice = Qt3DInput::QKeyboardDevice;
  using QMouseHandler = Qt3DInput::QMouseHandler;
  using QLogicalDevice = Qt3DInput::QLogicalDevice;
  using QAction = Qt3DInput::QAction;
  using QActionInput = Qt3DInput::QActionInput;
  using QMouseEvent = Qt3DInput::QMouseEvent;

private:
  OverlayWidget *infoSurface = new OverlayWidget(this);
  Scene *scene = new Scene();
  SpaceShip *spaceship = new SpaceShip(scene, this);
  Earth *earth = new Earth(scene);
  Sun *sun = new Sun(scene);
  Moon *moon = new Moon(scene);
  Mercury *mercury = new Mercury(scene);
  Venus *venus = new Venus(scene);
  Mars *mars = new Mars(scene);
  Jupiter *jupiter = new Jupiter(scene);
  Saturn *saturn = new Saturn(scene);
  Neptune *neptune = new Neptune(scene);
  Uranus *uranus = new Uranus(scene);

  CameraController *cameraController = new CameraController(scene);
  QFrameAction *frame = new QFrameAction(scene->getRoot());
  Starfield *starfield = new Starfield(scene);

  QKeyboardDevice *keyboardDevice = new QKeyboardDevice();
  QMouseDevice *mouseDevice = new QMouseDevice();
  QMouseHandler *mouseHandler = new QMouseHandler(scene->getRoot());
  QLogicalDevice *logicalDevice = new QLogicalDevice(scene->getRoot());
  QAction *upAction = new QAction();
  QAction *downAction = new QAction();
  QAction *leftAction = new QAction();
  QAction *rightAction = new QAction();
  QAction *forwardAction = new QAction();
  QAction *backwardAction = new QAction();
  QAction *escapeAction = new QAction();
  QAction *enterAction = new QAction();
  QActionInput *upActionInput = new QActionInput();
  QActionInput *downActionInput = new QActionInput();
  QActionInput *leftActionInput = new QActionInput();
  QActionInput *rightActionInput = new QActionInput();
  QActionInput *forwardActionInput = new QActionInput();
  QActionInput *backwardActionInput = new QActionInput();
  QActionInput *escapeActionInput = new QActionInput();
  QActionInput *enterActionInput = new QActionInput();

public:
  enum STATE { START = 0, MENU, GAMING, END } state = START;

public:
  Controller(QObject *parent = nullptr) : QObject(parent) {
    initInput();
    initScene();
  }
  Scene *getScene() { return scene; }
  virtual ~Controller() { delete scene; }

  bool isCollision(const QList<BoundingBox> &a, const QList<BoundingBox> &b);
  bool isCollision(const QList<BoundingBox> &a, const QVector3D &point);
  bool isCollision(const QList<BoundingBox> &a, const QVector3D &center,
                   const float &r);
  bool isCollision(const QVector3D &point, const QVector3D &center,
                   const float &r);

  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  STATE getState() { return state; }

  OverlayWidget *getInfoSurface() const;

  void addLaserBullet(const QVector3D &pos, const QVector3D &velocity);
  void addLaserBullet(const QVector3D &pos, const float &speed);

  void removeLaserBullet(LaserBullet *bullet);

  void spaceshipExplode(SpaceShip *spaceship);
public slots:
  void frameAction(float);

private:
  bool boxCollision(const BoundingBox &a, const BoundingBox &b);
  bool boxCollision(const BoundingBox &a, const QVector3D &center,
                    const float &r);
  bool lineCollision(const QVector3D &point, const QVector3D &line,
                     const BoundingBox &box);
  int pointCollision(const QVector3D &point, const QVector3D &line,
                     const QVector3D &check);
  void initInput();
  void initScene();
  void initCamera();
  void initPlanets();
  void initSpaceship();
  void initLight();
  void initFrameAction();

  void continueGame();
  void callOutMenu();
  void startGame();
  void gameOver();
};

#endif // CONTROLLER_H
