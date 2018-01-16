#ifndef BOUNDING_H
#define BOUNDING_H

#include <QVector3D>
#include <Qt3DCore/QTransform>

struct BoundingBox {
  using QTransform = Qt3DCore::QTransform;
  QVector3D point, x, y, z;
  const BoundingBox applyTransform(const QTransform &transform) const {
    return {transform.matrix().map(point), transform.matrix().map(x),
            transform.matrix().map(y), transform.matrix().map(z)};
  }
};

struct BoundingSphere {
  using QTransform = Qt3DCore::QTransform;
  QVector3D point;
  float radius;
  const BoundingSphere applyTransform(const QTransform &transform) const {
    return {transform.matrix().map(point), radius};
  }
};

#endif // BOUNDING_H
