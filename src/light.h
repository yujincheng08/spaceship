#ifndef LIGHT_H
#define LIGHT_H

#include "component.h"

class Light : public Component {
public:
  Light(QNode *parent = nullptr);
  virtual ~Light();
};

#endif // LIGHT_H
