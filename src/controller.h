#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "boundingbox.h"
#include "scene.h"
#include <QTime>

class Controller {
public:
  Controller();
  Scene *getScene();

public:
  bool isCollision(const QList<BoundingBox> &a, const QList<BoundingBox> &b);
  bool isCollision(const QList<BoundingBox> &a, const QVector3D &point);
  bool isCollision(const QList<BoundingBox> &a, const QVector3D &center,
                   const float &r);
  bool isCollision(const QVector3D &point, const QVector3D &center,
                   const float &r);

private:
  bool boxCollision(const BoundingBox &a, const BoundingBox &b);
  bool boxCollision(const BoundingBox &a, const QVector3D &center,
                    const float &r);
  bool lineCollision(const QVector3D &point, const QVector3D &line,
                     const BoundingBox &box);
  int pointCollision(const QVector3D &point, const QVector3D &line,
                     const QVector3D &check);

private:
  Scene *scene;
};

#endif // CONTROLLER_H
