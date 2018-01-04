#ifndef COMPONENT_H
#define COMPONENT_H

#define BITMAP_ID 0x4D42

#include <QString>
#include <QVector>
#include <QtOpenGL>

#include <gl/glaux.h>
#include <gl/glut.h>
#include <vector>

using namespace std;

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

class Component {
public:
  Component();
  void getPostion(GLdouble &a, GLdouble &b, GLdouble &c);
  void setSource(string filename);
  void copySourceFrom(Component *src);
  void setColor(int r, int g, int b, int a = 255);
  void setMaterial(int material);
  void setAmbient(GLfloat amb[]);
  void setDiffuse(GLfloat dif[]);
  void setSpecular(GLfloat spe[]);
  void setShininess(GLfloat shi);
  void setPosition(GLdouble px, GLdouble py, GLdouble pz);
  texture *LoadTexFile(const char *filename);
  bool LoadAllTextures();
  unsigned char *LoadBmpFile(const char *filename,
                             BITMAPINFOHEADER *bmpInfoHeader);
  virtual void repaint();

  enum Material {
    COPPER = 0,
    GOLD,
    SILVER,
    EMERALD,
    PEARL,
    RUBBER,
    LIGHTSILVER
  };

protected:
  GLdouble xPos, yPos, zPos;
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
