#ifndef COMPONENT_H
#define COMPONENT_H

#define BITMAP_ID 0x4D42

#include <QString>
#include <QVector>
#include <QtOpenGL>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QSceneLoader>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>

// reference: https://www.cnblogs.com/zjutlitao/p/4187529.html
struct POINT3 {
  double X;
  double Y;
  double Z;
};
struct WenLi {
  double TU;
  double TV;
};
struct FaXiangLiang {
  double NX;
  double NY;
  double NZ;
};
struct Mian {
  int V[3];
  int T[3];
  int N[3];
};

typedef struct {
  int width;           //纹理宽度
  int height;          //纹理高度
  unsigned int texID;  //纹理对象 ID
  unsigned char *data; //实际纹理数据
} texture;

class Component : public Qt3DCore::QEntity {
public:
  using QMesh = Qt3DRender::QMesh;
  using QTransform = Qt3DCore::QTransform;
  using QMaterial = Qt3DRender::QMaterial;
  using QTextureMaterial = Qt3DExtras::QTextureMaterial;
  using QTextureImage = Qt3DRender::QTextureImage;
  using QTexture2D = Qt3DRender::QTexture2D;
  using QSceneLoader = Qt3DRender::QSceneLoader;

public slots:
  virtual void frameAction(float dt) = 0;

public:
  Component(QNode *parent = nullptr);
  QVector3D getPostion() const;
  void setSource(const std::string &filename);
  void copySourceFrom(Component *src);
  void setColor(int r, int g, int b, int a = 255);
  void setMaterial(int material);
  void setAmbient(GLfloat amb[]);
  void setDiffuse(GLfloat dif[]);
  void setSpecular(GLfloat spe[]);
  void setShininess(GLfloat shi);
  void setPosition(QVector3D translation);

  enum Material {
    COPPER = 0,
    GOLD,
    SILVER,
    EMERALD,
    PEARL,
    RUBBER,
    LIGHTSILVER
  };
  virtual ~Component() {}

protected:
  QTransform *transform = new QTransform;
  GLdouble xRot, yRot, zRot;
  GLint r, g, b, a;
  GLfloat ambient[4], diffuse[4], specular[4], shininess;

  texture *spaceship, *earth;

  QVector<POINT3> V;
  QVector<WenLi> VT;
  QVector<FaXiangLiang> VN;
  QVector<Mian> F;
};

#endif // COMPONENT_H
