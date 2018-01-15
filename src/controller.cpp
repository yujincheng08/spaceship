#include "controller.h"

Controller::Controller() {
  qsrand(time(NULL));
  scene = new Scene;
}

Scene *Controller::getScene() { return scene; }

bool Controller::isCollision(const QList<BoundingBox> &a,
                             const QList<BoundingBox> &b) {
  for (BoundingBox boxa : a)
    for (BoundingBox boxb : b)
      if (boxCollision(boxa, boxb))
        return true;
  return false;
}

bool Controller::isCollision(const QList<BoundingBox> &a,
                             const QVector3D &point) {
  for (BoundingBox box : a) {
    if (pointCollision(box.point, box.x, point) == 0 &&
        pointCollision(box.point, box.y, point) == 0 &&
        pointCollision(box.point, box.z, point) == 0)
      return true;
  }
  return false;
}

bool Controller::isCollision(const QList<BoundingBox> &a,
                             const QVector3D &center, const float &r) {
  for (BoundingBox box : a)
    if (boxCollision(box, center, r))
      return true;
  return false;
}

bool Controller::isCollision(const QVector3D &point, const QVector3D &center,
                             const float &r) {
  return (center - point).length() < r;
}

bool Controller::boxCollision(const BoundingBox &a, const BoundingBox &b) {
  bool xCollision = lineCollision(a.point, a.x, b),
       yCollision = lineCollision(a.point, a.y, b),
       zCollision = lineCollision(a.point, a.z, b);
  return xCollision && yCollision && zCollision;
}

bool Controller::boxCollision(const BoundingBox &a, const QVector3D &center,
                              const float &r) {
  if (pointCollision(a.point, a.x, center) == 0 &&
      pointCollision(a.point, a.y, center) == 0 &&
      pointCollision(a.point, a.z, center) == 0)
    return true;
}

bool Controller::lineCollision(const QVector3D &point, const QVector3D &line,
                               const BoundingBox &box) {
  bool left = false, right = false;
  QVector3D checkPoint;

  for (int i = 0; i < 8; i++) {
    checkPoint = box.point;
    if (i & 1 != 0)
      checkPoint += box.x;
    if (i & 2 != 0)
      checkPoint += box.y;
    if (i & 4 != 0)
      checkPoint += box.z;
    switch (pointCollision(point, line, checkPoint)) {
    case 0:
      return true;
    case 1:
      left = true;
      break;
    case 2:
      right = true;
      break;
    }

    if (left && right)
      return true;
  }
  return false;
}

int Controller::pointCollision(const QVector3D &point, const QVector3D &line,
                               const QVector3D &check) {

  QVector3D a = check - point;
  if (QVector3D::dotProduct(a, line) <= 0)
    return 1;
  a -= line;
  if (QVector3D::dotProduct(a, line) >= 0)
    return 2;

  return 0;
}
