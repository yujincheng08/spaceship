#ifndef MYLIGHT_H
#define MYLIGHT_H

#include <QtOpenGL>

class MyLight {
public:
  MyLight();
  MyLight(GLint number);
  ~MyLight();
  void setAmbient(GLfloat a[]);
  void setDiffuse(GLfloat a[]);
  void setSpecular(GLfloat a[]);
  void setPosition(GLfloat a[]);
  void initLight();
  void lightOn();
  void lightOff();
  boolean isOn();

private:
  GLfloat *ambient, *diffuse, *specular, *position;

  boolean isLightOn;

  GLint number;
};

#endif // MYLIGHT_H
