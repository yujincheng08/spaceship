#ifndef PLANETMATERIAL_H
#define PLANETMATERIAL_H

#include <QVector3D>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QTextureWrapMode>

class PlanetMaterial : public Qt3DRender::QMaterial {
  using QMaterial = Qt3DRender::QMaterial;
  using QParameter = Qt3DRender::QParameter;
  using QTechnique = Qt3DRender::QTechnique;
  using QTexture2D = Qt3DRender::QTexture2D;
  using QTextureImage = Qt3DRender::QTextureImage;
  using QTextureWrapMode = Qt3DRender::QTextureWrapMode;

private:
  QParameter *ambientParameter = new QParameter(this);
  QParameter *diffuseParameter = new QParameter(this);
  QParameter *specularParameter = new QParameter(this);
  QParameter *shinessParameter = new QParameter(this);
  QParameter *diffuseTextureParameter = new QParameter(this);
  QParameter *specularTextureParameter = new QParameter(this);
  QParameter *normalTextureParameter = new QParameter(this);
  QParameter *texCoordScaleParameter = new QParameter(this);
  QParameter *opacityParameter = new QParameter(this);
  QTexture2D *diffuseTexture = new QTexture2D(this);
  QTexture2D *specularTexture = new QTexture2D(this);
  QTexture2D *normalTexture = new QTexture2D(this);
  QTextureImage *diffuseImage = new QTextureImage;
  QTextureImage *specularImage = new QTextureImage;
  QTextureImage *normalImage = new QTextureImage;

public:
  PlanetMaterial(QNode *parent = nullptr);
  void setAmbient(const QColor &color) {
    ambientParameter->setValue(QVector3D{
        (float)color.redF(), (float)color.greenF(), (float)color.greenF()});
  }
  void setDiffuse(const QColor &color) {
    diffuseParameter->setValue(QVector3D{
        (float)color.redF(), (float)color.greenF(), (float)color.greenF()});
  }
  void setSpecular(const QColor &color) {
    specularParameter->setValue(QVector3D{
        (float)color.redF(), (float)color.greenF(), (float)color.greenF()});
  }
  void setShiness(const qreal &value) { shinessParameter->setValue(value); }
  void setDiffuseTexture(const QString &path) {
    diffuseImage->setSource(QUrl(path));
  }
  void setSpecularTexture(const QString &path) {
    specularImage->setSource(QUrl(path));
  }
  void setNormalTexture(const QString &path) {
    normalImage->setSource(QUrl(path));
  }
  void setTexCoordScale(const qreal &value) {
    texCoordScaleParameter->setValue(value);
  }
  void setOpacity(const qreal &value) { opacityParameter->setValue(value); }
};

#endif // PLANETMATERIAL_H
