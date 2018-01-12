#include "mylight.h"

MyLight::MyLight() {}

MyLight::MyLight(GLint number) {
  this->number = number;
  ambient = new GLfloat[4]();
  diffuse = new GLfloat[4]();
  specular = new GLfloat[4]();
  position = new GLfloat[4]();
  GLfloat amb[] = {0.5, 0.5, 0.5, 1}, dif[] = {1, 1, 1, 1},
          spe[] = {1, 1, 1, 1}, pos[] = {0, 0, 1, 0};
  for (int i = 0; i < 4; i++) {
    ambient[i] = amb[i];
    diffuse[i] = dif[i];
    specular[i] = spe[i];
    position[i] = pos[i];
  }
  initLight();
  lightOn();
}

MyLight::~MyLight() {
  delete[] ambient;
  delete[] diffuse;
  delete[] specular;
  delete[] position;
}

void MyLight::setAmbient(GLfloat a[]) {
  for (int i = 0; i < 4; i++)
    ambient[i] = a[i];
  glLightfv(number, GL_AMBIENT, ambient); //环境光
}

void MyLight::setDiffuse(GLfloat a[]) {
  for (int i = 0; i < 4; i++)
    diffuse[i] = a[i];
  glLightfv(number, GL_DIFFUSE, diffuse); //漫射光
}

void MyLight::setSpecular(GLfloat a[]) {
  for (int i = 0; i < 4; i++)
    specular[i] = a[i];
  glLightfv(number, GL_SPECULAR, specular); //镜面反射
}

void MyLight::setPosition(GLfloat a[]) {
  for (int i = 0; i < 4; i++)
    position[i] = a[i];
  glLightfv(number, GL_POSITION, position); //光照位置
}

void MyLight::initLight() {
  glLightfv(number, GL_AMBIENT, ambient);   //环境光
  glLightfv(number, GL_DIFFUSE, diffuse);   //漫射光
  glLightfv(number, GL_SPECULAR, specular); //镜面反射
  glLightfv(number, GL_POSITION, position); //光照位置

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

void MyLight::lightOn() {
  glEnable(number);
  glEnable(GL_LIGHTING);
  isLightOn = true;
}

void MyLight::lightOff() {
  glDisable(number);
  isLightOn = false;
}

bool MyLight::isOn() { return isLightOn; }
