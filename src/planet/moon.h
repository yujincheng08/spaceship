#ifndef MOON_H
#define MOON_H

#include "planet.h"

class Moon : public Planet {
public:
  Moon(Scene *parent = nullptr);
};

#endif // MOON_H
