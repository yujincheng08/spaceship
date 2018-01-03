#include "mycamera.h"

MyCamera::MyCamera() {
  resetView();
  step = 0.5;
  rotate = 0.5;
}

void MyCamera::setView() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void MyCamera::resetView() {
  setEye(0, -20, 20);
  setCenter(0, 0, 0);
  setUp(0, 1, 1);
}

void MyCamera::setEye(GLdouble ex, GLdouble ey, GLdouble ez) {
  if (ex == centerx && ey == centery && ez == centerz)
    return;
  eyex = ex;
  eyey = ey;
  eyez = ez;
  setUp(upx, upy, upz);
}

void MyCamera::setCenter(GLdouble cx, GLdouble cy, GLdouble cz) {
  if (cx == eyex && cy == eyey && cz == eyez)
    return;
  centerx = cx;
  centery = cy;
  centerz = cz;
  setUp(upx, upy, upz);
}

void MyCamera::setUp(GLdouble ux, GLdouble uy, GLdouble uz) {
  GLdouble viewx = centerx - eyex, viewy = centery - eyey,
           viewz = centerz - eyez;

  double view[3] = {viewx, viewy, viewz}, up[3] = {ux, uy, uz};

  double length =
      MyVector::dotMulti(view, up, 3) / MyVector::dotMulti(view, view, 3);
  MyVector::kMulti(view, 3, length);
  Vct upVec = MyVector::sub(up, view, 3);
  MyVector::unit(upVec, 3);

  upx = upVec[0];
  upy = upVec[1];
  upz = upVec[2];

  delete[] upVec;
}

void MyCamera::posMove(GLdouble mx, GLdouble my, GLdouble mz) {
  GLdouble viewx = centerx - eyex, viewy = centery - eyey,
           viewz = centerz - eyez;

  double view[3] = {viewx, viewy, viewz}, up[3] = {upx, upy, upz};

  // move left & right
  Vct product = MyVector::crossMulti3(view, up);
  MyVector::unit(product, 3);
  MyVector::kMulti(product, 3, step);
  centerx += mx * product[0];
  centery += mx * product[1];
  centerz += mx * product[2];
  eyex += mx * product[0];
  eyey += mx * product[1];
  eyez += mx * product[2];
  delete[] product;

  // move up & down
  MyVector::kMulti(up, 3, step);
  centerx += my * up[0];
  centery += my * up[1];
  centerz += my * up[2];
  eyex += my * up[0];
  eyey += my * up[1];
  eyez += my * up[2];

  // move front & back
  MyVector::unit(view, 3);
  MyVector::kMulti(view, 3, step);
  centerx += mz * view[0];
  centery += mz * view[1];
  centerz += mz * view[2];
  eyex += mz * view[0];
  eyey += mz * view[1];
  eyez += mz * view[2];
}

void MyCamera::viewRotate(GLdouble lr, GLdouble ud) {
  GLdouble viewx = centerx - eyex, viewy = centery - eyey,
           viewz = centerz - eyez;

  double view[3] = {viewx, viewy, viewz}, up[3] = {upx, upy, upz};

  // rotate left & right
  if (lr != 0) {
    Vct product = MyVector::crossMulti3(view, up);
    MyVector::unit(product, 3);
    MyVector::kMulti(product, 3, rotate);
    for (int i = 0; i < 3; i++)
      view[i] += lr * product[i];
    MyVector::unit(view, 3);
    MyVector::kMulti(view, 3,
                     sqrt(viewx * viewx + viewy * viewy + viewz * viewz));
    delete[] product;
  }

  // rotate up & down
  if (ud != 0) {
    for (int i = 0; i < 3; i++)
      view[i] -= ud * up[i];
    MyVector::unit(view, 3);
    MyVector::kMulti(view, 3,
                     sqrt(viewx * viewx + viewy * viewy + viewz * viewz));
  }

  centerx = eyex + view[0];
  centery = eyey + view[1];
  centerz = eyez + view[2];
  setUp(upx, upy, upz);
  upx = up[0];
  upy = up[1];
  upz = up[2];
}

void MyCamera::viewRound(GLdouble lr, GLdouble ud) {
  GLdouble viewx = centerx - eyex, viewy = centery - eyey,
           viewz = centerz - eyez;

  double view[3] = {viewx, viewy, viewz}, up[3] = {upx, upy, upz};

  // rotate left & right
  if (lr != 0) {
    Vct product = MyVector::crossMulti3(view, up);
    MyVector::unit(product, 3);
    MyVector::kMulti(product, 3, rotate);

    for (int i = 0; i < 3; i++)
      view[i] -= lr * product[i];
    MyVector::unit(view, 3);
    MyVector::kMulti(view, 3,
                     sqrt(viewx * viewx + viewy * viewy + viewz * viewz));
    delete[] product;
  }

  // rotate up & down
  if (ud != 0) {
    for (int i = 0; i < 3; i++)
      view[i] += ud * up[i];
    MyVector::unit(view, 3);
    MyVector::kMulti(view, 3,
                     sqrt(viewx * viewx + viewy * viewy + viewz * viewz));
  }

  eyex = centerx - view[0];
  eyey = centery - view[1];
  eyez = centerz - view[2];
  setUp(upx, upy, upz);
  upx = up[0];
  upy = up[1];
  upz = up[2];
}
