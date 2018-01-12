//#include "mycamera.h"
//#include "component.h"

// MyCamera::MyCamera() {
//  resetView();
//  step = 0.5;
//  rotate = 0.5;
//  trace = NULL;
//  offset = 0;
//}

// void MyCamera::setView() {
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//  gluLookAt(eye.x(), eye.y(), eye.z(), center.x(), center.y(), center.z(),
//            up.x(), up.y(), up.z());
//}

// void MyCamera::resetView() {
//  setEye({0, 10, 25});
//  setCenter({0, 0, 0});
//  setUp({0, 1, -1});
//}

// void MyCamera::setEye(const QVector3D &newEye) {
//  eye = newEye;
//  setUp(up);
//}

// void MyCamera::setCenter(const QVector3D &newCenter) {
//  center = newCenter;
//  setUp(up);
//}

// void MyCamera::setUp(const QVector3D &newUp) {
//  QVector3D view = center - eye;

//  float length = QVector3D::dotProduct(view, newUp) / view.lengthSquared();
//  view *= length;
//  up = newUp - view;
//  up.normalize();
//}

// void MyCamera::traceComponent(const Component *cpnt, GLdouble off) {
//  trace = cpnt;
//  offset = off;
//}

// void MyCamera::keepTrace() {
//  if (trace == nullptr)
//    return;
//  QVector3D position = trace->getPostion();
//  setEye(position - center + eye);
//  setCenter({position.x(), position.y() + offset, position.z()});
//  setUp({0, 1, 0});
//  setView();
//}

// void MyCamera::posMove(const QVector3D &shift) {
//  QVector3D view = center - eye;
//  // move left & right
//  QVector3D product = QVector3D::crossProduct(view, up);
//  product.normalize();
//  product *= step;
//  eye += shift.x() * product;
//  if (trace == nullptr) {
//    center += shift.x() * product;
//  }
//  up *= step;
//  eye += shift.y() * up;
//  if (trace == nullptr) {
//    center += shift.y() * up;
//  }
//  view.normalize();
//  view *= step;
//  eye += shift.z() * view;
//  if (trace == nullptr) {
//    center += shift.z() * view;
//  }
//}

//// void MyCamera::viewRotate(GLdouble lr, GLdouble ud) {
////  if (trace != NULL)
////    return;

////  GLdouble viewx = centerx - eyex, viewy = centery - eyey,
////           viewz = centerz - eyez;

////  double view[3] = {viewx, viewy, viewz}, up[3] = {upx, upy, upz};

////  // rotate left & right
////  if (lr != 0) {
////    Vct product = MyVector::crossMulti3(view, up);
////    MyVector::unit(product, 3);
////    MyVector::kMulti(product, 3, rotate);
////    for (int i = 0; i < 3; i++)
////      view[i] += lr * product[i];
////    MyVector::unit(view, 3);
////    MyVector::kMulti(view, 3,
////                     sqrt(viewx * viewx + viewy * viewy + viewz * viewz));
////    delete[] product;
////  }

////  // rotate up & down
////  if (ud != 0) {
////    for (int i = 0; i < 3; i++)
////      view[i] -= ud * up[i];
////    MyVector::unit(view, 3);
////    MyVector::kMulti(view, 3,
////                     sqrt(viewx * viewx + viewy * viewy + viewz * viewz));
////  }

////  centerx = eyex + view[0];
////  centery = eyey + view[1];
////  centerz = eyez + view[2];
////  setUp(upx, upy, upz);
////  upx = up[0];
////  upy = up[1];
////  upz = up[2];
////}

// void MyCamera::viewRound(qreal lr, qreal ud) {
//  QVector3D l = center - eye;
//  QVector3D c;
//  c = QVector3D::crossProduct(up, l);
//  c.normalize();
//  c *= -lr;

//  float len = l.length();
//  l += c;
//  l -= up * ud / 3;
//  l.normalize();
//  l *= len;

//  eye = center - l;

//  setUp({0, 1, 0});
//}
