#ifndef INFOSURFACE_H
#define INFOSURFACE_H

#include <QPainter>
#include <QWidget>

class MainWindow;

class InfoSurface : public QWidget {
  Q_OBJECT
public:
  explicit InfoSurface(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *e);

private:
  MainWindow *ftr;
  int shootSize;
};

#endif // INFOSURFACE_H
