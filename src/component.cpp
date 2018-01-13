#include "component.h"
#include <QBitmap>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
// reference: https://www.cnblogs.com/zjutlitao/p/4187529.html
Component::Component(QNode *parent) : QEntity(parent) {
  addComponent(transform);
}

QVector3D Component::getPostion() const { return transform->translation(); }

void Component::setPosition(QVector3D translation) {
  transform->setTranslation(translation);
}
