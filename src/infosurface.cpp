#include "infosurface.h"

InfoSurface::InfoSurface(QWidget *parent) : QWidget(parent) {
  setParent(parent);
  setGeometry(0, 0, 960, 540);
  shootSize = 10;
  show();
}

void InfoSurface::paintEvent(QPaintEvent *e) {
  QPainter pter(this);
  pter.setPen(Qt::white);
  pter.drawLine(this->width() / 2 - shootSize, this->height() / 2,
                this->width() / 2 + shootSize, this->height() / 2);
  pter.drawLine(this->width() / 2, this->height() / 2 - shootSize,
                this->width() / 2, this->height() / 2 + shootSize);
  pter.end();
}
