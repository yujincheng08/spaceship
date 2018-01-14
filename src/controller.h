#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "scene.h"

class Controller {
public:
  Controller();
  Scene *getScene();

private:
  bool boxCollision();

private:
  Scene *scene;
};

#endif // CONTROLLER_H
