#include "mycamera.h"
#include "component.h"

MyCamera::MyCamera() {
  resetView();
  step = 0.5;
  rotate = 0.5;
  trace = NULL;
  offset = 0;
}

void MyCamera::setView() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void MyCamera::resetView() {
  setEye(0, 10, 25);
  setCenter(0, 0, 0);
  setUp(0, 1, -1);
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
  QVector3D view(centerx - eyex, centery - eyey, centerz - eyez),
      up(ux, uy, uz);

  float length = QVector3D::dotProduct(view, up) / view.lengthSquared();
  view *= length;
  up -= view;
  up.normalize();

  upx = up.x();
  upy = up.y();
  upz = up.z();
}

void MyCamera::traceComponent(Component *cpnt, GLdouble off) {
  trace = cpnt;
  GLdouble x, y, z;
  trace->getPostion(x, y, z);
  offset = off;
}

void MyCamera::keepTrace() {
  if (trace == NULL)
    return;
  GLdouble x, y, z;
  trace->getPostion(x, y, z);
  setEye(x - centerx + eyex, y - centery + eyey + offset, z - centerz + eyez);
  setCenter(x, y + offset, z);
  setUp(0, 1, 0);
  setView();
}

void MyCamera::posMove(GLdouble mx, GLdouble my, GLdouble mz) {
  QVector3D view(centerx - eyex, centery - eyey, centerz - eyez),
      up(upx, upy, upz);

  // move left & right
  QVector3D product = QVector3D::crossProduct(view, up);
  product.normalize();
  product *= step;
  eyex += mx * product.x();
  eyey += mx * product.y();
  eyez += mx * product.z();
  if (trace == NULL) {
    centerx += mx * product.x();
    centery += mx * product.y();
    centerz += mx * product.z();
  }

  // move up & down
  up *= step;
  eyex += my * up.x();
  eyey += my * up.y();
  eyez += my * up.z();
  if (trace == NULL) {
    centerx += my * up.x();
    centery += my * up.y();
    centerz += my * up.z();
  }

  // move front & back
  view.normalize();
  view *= step;
  eyex += mz * view.x();
  eyey += mz * view.y();
  eyez += mz * view.z();
  if (trace == NULL) {
    centerx += mz * view.x();
    centery += mz * view.y();
    centerz += mz * view.z();
  }
}

// void MyCamera::viewRotate(GLdouble lr, GLdouble ud) {
//  if (trace != NULL)
//    return;

//  GLdouble viewx = centerx - eyex, viewy = centery - eyey,
//           viewz = centerz - eyez;

//  double view[3] = {viewx, viewy, viewz}, up[3] = {upx, upy, upz};

//  // rotate left & right
//  if (lr != 0) {
//    Vct product = MyVector::crossMulti3(view, up);
//    MyVector::unit(product, 3);
//    MyVector::kMulti(product, 3, rotate);
//    for (int i = 0; i < 3; i++)
//      view[i] += lr * product[i];
//    MyVector::unit(view, 3);
//    MyVector::kMulti(view, 3,
//                     sqrt(viewx * viewx + viewy * viewy + viewz * viewz));
//    delete[] product;
//  }

//  // rotate up & down
//  if (ud != 0) {
//    for (int i = 0; i < 3; i++)
//      view[i] -= ud * up[i];
//    MyVector::unit(view, 3);
//    MyVector::kMulti(view, 3,
//                     sqrt(viewx * viewx + viewy * viewy + viewz * viewz));
//  }

//  centerx = eyex + view[0];
//  centery = eyey + view[1];
//  centerz = eyez + view[2];
//  setUp(upx, upy, upz);
//  upx = up[0];
//  upy = up[1];
//  upz = up[2];
//}

void MyCamera::viewRound(GLdouble lr, GLdouble ud) {
  QVector3D l(centerx - eyex, centery - eyey, centerz - eyez), u(upx, upy, upz);

  QVector3D c;
  c = QVector3D::crossProduct(u, l);
  c.normalize();
  c *= -lr;

  float len = l.length();
  l += c;
  l -= u * ud / 3;
  l.normalize();
  l *= len;

  eyex = centerx - l.x();
  eyey = centery - l.y();
  eyez = centerz - l.z();

  setUp(0, 1, 0);
}
