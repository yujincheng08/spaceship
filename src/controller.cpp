#include "controller.h"

Controller::Controller() { scene = new Scene; }

Scene *Controller::getScene() { return scene; }
