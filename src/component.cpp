#include "component.h"
#include <QBitmap>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
// reference: https://www.cnblogs.com/zjutlitao/p/4187529.html
Component::Component(QNode *parent) : QEntity(parent) {
  xPos = yPos = zPos = 0;
  xRot = yRot = zRot = 0;
  // LoadAllTextures();
  // setMaterial(LIGHTSILVER);
  qDebug() << "component constructed.";
}

QVector3D Component::getPostion() const { return {xPos, yPos, zPos}; }

void Component::setSource(const string &filename) {
  QFile inputFile(QString::fromStdString(filename));
  inputFile.open(QIODevice::ReadOnly);

  QTextStream ifs(&inputFile); // cube bunny Eight
  string s;
  Mian *f;
  POINT3 *v;
  FaXiangLiang *vn;
  WenLi *vt;

  while (!ifs.atEnd()) {
    s = ifs.readLine().toStdString();
    if (s.length() < 2)
      continue;
    if (s[0] == 'v') {
      if (s[1] == 't') { // vt 0.581151 0.979929 纹理
        istringstream in(s);
        vt = new WenLi();
        string head;
        in >> head >> vt->TU >> vt->TV;
        VT.push_back(*vt);

      } else if (s[1] == 'n') { // vn 0.637005 -0.0421857 0.769705 法向量
        istringstream in(s);
        vn = new FaXiangLiang();
        string head;
        in >> head >> vn->NX >> vn->NY >> vn->NZ;
        VN.push_back(*vn);

      } else { // v -53.0413 158.84 -135.806 点
        istringstream in(s);
        v = new POINT3();
        string head;
        in >> head >> v->X >> v->Y >> v->Z;
        V.push_back(*v);
      }

    } else if (s[0] == 'f') { // f 2443//2656 2442//2656 2444//2656 面
      for (int k = s.size() - 1; k >= 0; k--) {
        if (s[k] == '/')
          s[k] = ' ';
      }
      istringstream in(s);
      f = new Mian();
      string head;
      in >> head;
      int i = 0;
      while (i < 3) {
        if (V.size() != 0) {
          in >> f->V[i];
          f->V[i] -= 1;
        }
        if (VT.size() != 0) {
          in >> f->T[i];
          f->T[i] -= 1;
        }
        if (VN.size() != 0) {
          in >> f->N[i];
          f->N[i] -= 1;
        }
        i++;
      }
      F.push_back(*f);
    }
  }
}

void Component::copySourceFrom(Component *src) {
  V.append(src->V);
  VT.append(src->VT);
  VN.append(src->VN);
  F.append(src->F);
}

void Component::setColor(int r, int g, int b, int a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

void Component::setMaterial(int material) {
  switch (material) {
  case COPPER: {
    GLfloat amb[] = {0.191250, 0.073500, 0.022500, 1.000000},
            dif[] = {0.703800, 0.270480, 0.082800, 1.000000},
            spe[] = {0.256777, 0.137622, 0.086014, 1.000000}, shi = 12.800000;
    setAmbient(amb);
    setDiffuse(dif);
    setSpecular(spe);
    setShininess(shi);
    break;
  }
  case GOLD: {
    GLfloat amb[] = {0.247250, 0.199500, 0.074500, 1.000000},
            dif[] = {0.751640, 0.606480, 0.226480, 1.000000},
            spe[] = {0.628281, 0.555802, 0.366065, 1.000000}, shi = 51.200001;
    setAmbient(amb);
    setDiffuse(dif);
    setSpecular(spe);
    setShininess(shi);
    break;
  }
  case SILVER: {
    GLfloat amb[] = {0.192250, 0.192250, 0.192250, 1.000000},
            dif[] = {0.507540, 0.507540, 0.507540, 1.000000},
            spe[] = {0.508273, 0.508273, 0.508273, 1.000000}, shi = 51.200001;
    setAmbient(amb);
    setDiffuse(dif);
    setSpecular(spe);
    setShininess(shi);
    break;
  }
  case LIGHTSILVER: {

    GLfloat amb[] = {0.231250, 0.231250, 0.231250, 1.000000},
            dif[] = {0.277500, 0.277500, 0.277500, 1.000000},
            spe[] = {0.773911, 0.773911, 0.773911, 1.000000}, shi = 89.599998;
    setAmbient(amb);
    setDiffuse(dif);
    setSpecular(spe);
    setShininess(shi);
    break;
  }
  case EMERALD: {
    GLfloat amb[] = {0.021500, 0.174500, 0.021500, 0.550000},
            dif[] = {0.075680, 0.614240, 0.075680, 0.550000},
            spe[] = {0.633000, 0.727811, 0.633000, 0.550000}, shi = 76.800003;
    setAmbient(amb);
    setDiffuse(dif);
    setSpecular(spe);
    setShininess(shi);
    break;
  }
  case PEARL: {
    GLfloat amb[] = {0.250000, 0.207250, 0.207250, 0.922000},
            dif[] = {1.000000, 0.829000, 0.829000, 0.922000},
            spe[] = {0.296648, 0.296648, 0.296648, 0.922000}, shi = 11.264000;
    setAmbient(amb);
    setDiffuse(dif);
    setSpecular(spe);
    setShininess(shi);
    break;
  }
  case RUBBER: {
    GLfloat amb[] = {0.020000, 0.020000, 0.020000, 1.000000},
            dif[] = {0.010000, 0.010000, 0.010000, 1.000000},
            spe[] = {0.400000, 0.400000, 0.400000, 1.000000}, shi = 10.000000;
    setAmbient(amb);
    setDiffuse(dif);
    setSpecular(spe);
    setShininess(shi);
    break;
  }
  }
}

void Component::setAmbient(GLfloat amb[]) {
  for (int i = 0; i < 4; i++)
    ambient[i] = amb[i];
}

void Component::setDiffuse(GLfloat dif[]) {
  for (int i = 0; i < 4; i++)
    diffuse[i] = dif[i];
}

void Component::setSpecular(GLfloat spe[]) {
  for (int i = 0; i < 4; i++)
    specular[i] = spe[i];
}

void Component::setShininess(GLfloat shi) { shininess = shi; }

void Component::setPosition(qreal px, qreal py, qreal pz) {
  xPos = px;
  yPos = py;
  zPos = pz;
}
