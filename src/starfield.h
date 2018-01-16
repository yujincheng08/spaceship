#ifndef STARFIELD_H
#define STARFIELD_H

#include "component.h"
#include <planet/planeteffect.h>
#include <planet/planetlight.h>
#include <planet/planetmaterial.h>

class Starfield : public Component {
private:
  QMesh *mesh = new QMesh(this);
  PlanetMaterial *material = new PlanetMaterial(this);
  PlanetEffect *effect = new PlanetEffect(this);
  PlanetLight *light = new PlanetLight(this);
  QTextureImage *textureImage = new QTextureImage;
  QTexture2D *texture = new QTexture2D(this);

protected slots:
  void frameAction(float) override {}

public:
  Starfield(Scene *parent = nullptr);

private:
};

#endif // STARFIELD_H
