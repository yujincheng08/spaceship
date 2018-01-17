#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <QtMath>

typedef double *Vct;

class MyVector {
public:
  MyVector();
  static double dotMulti(Vct a, Vct b, int num);
  static Vct crossMulti3(Vct a, Vct b);
  static void unit(Vct v, int num);
  static void kMulti(Vct v, int num, double kMulti);
  static Vct add(Vct a, Vct b, int num);
  static Vct sub(Vct a, Vct b, int num);
  static double angle(Vct a, Vct b, int num);
};

#endif // MYVECTOR_H
