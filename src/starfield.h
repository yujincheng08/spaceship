#ifndef STARFIELD_H
#define STARFIELD_H

#include "component.h"
#include <Qt3DExtras/QDiffuseMapMaterial>

class Starfield : public Component {
public:
  using QDiffuseMapMaterial = Qt3DExtras::QDiffuseMapMaterial;

private:
  QMesh *mesh = new QMesh(this);
  QDiffuseMapMaterial *material = new QDiffuseMapMaterial(this);
  QTextureImage *textureImage = new QTextureImage;
  QTexture2D *texture = new QTexture2D(this);

protected slots:
  void frameAction(float) override {}

public:
  Starfield(Scene *parent = nullptr);

private:
};

#endif // STARFIELD_H
