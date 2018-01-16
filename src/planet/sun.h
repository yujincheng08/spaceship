#ifndef SUN_H
#define SUN_H

#include "planet.h"

class Sun : public Planet {
public:
  Sun(Scene *parent = nullptr);
};

#endif // SUN_H
