#ifndef BOUNDING_H
#define BOUNDING_H

#include <QVector3D>
#include <Qt3DCore/QTransform>

struct BoundingBox {
  using QTransform = Qt3DCore::QTransform;
  QVector3D point, x, y, z;
  const BoundingBox applyTransform(const QTransform &transform) const {
    auto mappedPoint = transform.matrix().map(point);
    return {mappedPoint, transform.matrix().map(x) - mappedPoint,
            transform.matrix().map(y) - mappedPoint,
            transform.matrix().map(z) - mappedPoint};
  }
};

struct BoundingSphere {
  using QTransform = Qt3DCore::QTransform;
  QVector3D center;
  float radius;
  const BoundingSphere applyTransform(const QTransform &transform) const {
    return {transform.matrix().map(center), radius};
  }
};

#endif // BOUNDING_H
