#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QtOpenGL>
#include <gl/glaux.h>
#include <gl/glut.h>
#include <vector>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut.lib")
#pragma comment(lib, "glaux.lib")

using namespace std;

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

class Component {
public:
  Component();
  void getPostion(GLdouble &a, GLdouble &b, GLdouble &c);
  void setSource(string filename);
  void setColor(int r, int g, int b, int a = 255);
  void setMaterial(int material);
  void setAmbient(GLfloat amb[]);
  void setDiffuse(GLfloat dif[]);
  void setSpecular(GLfloat spe[]);
  void setShininess(GLfloat shi);
  void repaint();
  void LoadTexture(char *filename, GLuint &texture);

  enum Material {
    COPPER = 0,
    GOLD,
    SILVER,
    EMERALD,
    PEARL,
    RUBBER,
    LIGHTSILVER
  };

private:
  GLdouble xPos, yPos, zPos;
  GLdouble xRot, yRot, zRot;
  GLint r, g, b, a;
  GLfloat ambient[4], diffuse[4], specular[4], shininess;
  UINT g_bmp[1];
  vector<POINT3> V;
  vector<WenLi> VT;
  vector<FaXiangLiang> VN;
  vector<Mian> F;
};

#endif // COMPONENT_H
