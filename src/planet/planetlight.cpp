#include "planetlight.h"

PlanetLight::PlanetLight(QNode *parent) : QEntity(parent) {
  lightCamera->setObjectName("lightCameraLens");
  lightCamera->setProjectionType(QCameraLens::PerspectiveProjection);
  lightCamera->setFieldOfView(30);
  lightCamera->setNearPlane(2500000.0f);
  lightCamera->setFarPlane(10000000.0f);
  lightCamera->setPosition(QVector3D{0.0f, 0.0f, 0.0f});
  lightCamera->setViewCenter(QVector3D{0.0f, 0.0f, 0.0f});
  lightCamera->setUpVector(QVector3D{0.0f, 1.0f, 0.0f});
}
