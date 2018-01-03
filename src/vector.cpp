#include "vector.h"

#define MINIMIZE 0.0001

MyVector::MyVector() {}

double MyVector::dotMulti(Vct a, Vct b, int num) {
  int ans = 0;
  for (int i = 0; i < num; i++) {
    ans += a[i] * b[i];
  }
  return ans;
}

Vct MyVector::crossMulti3(Vct a, Vct b) {
  Vct ans;
  ans = new double[3];

  ans[0] = a[1] * b[2] - a[2] * b[1];
  ans[1] = a[2] * b[0] - a[0] * b[2];
  ans[2] = a[0] * b[1] - a[1] * b[0];

  return ans;
}

void MyVector::unit(Vct v, int num) {
  double length = 0;
  for (int i = 0; i < num; i++)
    length += v[i] * v[i];
  length = sqrt(length);
  if (length < MINIMIZE && length > -MINIMIZE)
    return;
  for (int i = 0; i < num; i++)
    v[i] /= length;
}

void MyVector::kMulti(Vct v, int num, double length) {
  for (int i = 0; i < num; i++)
    v[i] *= length;
}

Vct MyVector::sub(Vct a, Vct b, int num) {
  Vct ans;
  ans = new double[num];

  for (int i = 0; i < num; i++)
    ans[i] = a[i] - b[i];

  return ans;
}

double MyVector::angle(Vct a, Vct b, int num) {
  return acos(MyVector::dotMulti(a, b, num) /
              sqrt(MyVector::dotMulti(a, a, num)) /
              sqrt(MyVector::dotMulti(b, b, num)));
}
