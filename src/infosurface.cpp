#include "infosurface.h"
#include "component.h"
#include "mainwindow.h"
#include "spaceship.h"

InfoSurface::InfoSurface(QWidget *parent) : QWidget(parent) {
  setParent(parent);
  ftr = (MainWindow *)parent;
  setGeometry(0, 0, 960, 540);
  shootSize = 10;
  show();
}

void InfoSurface::paintEvent(QPaintEvent *e) {
  //  QPainter pter(this);
  //  pter.setPen(Qt::white);
  //  pter.drawLine(this->width() / 2 - shootSize, this->height() / 2,
  //                this->width() / 2 + shootSize, this->height() / 2);
  //  pter.drawLine(this->width() / 2, this->height() / 2 - shootSize,
  //                this->width() / 2, this->height() / 2 + shootSize);

  //  SpaceShip *ss = (SpaceShip *)(ftr->components.at(0));
  //  pter.drawText(0, 20, "Position:");
  //  pter.drawText(0, 40,
  //                QString::number(ss->xPos) + " " + QString::number(ss->yPos)
  //                +
  //                    " " + QString::number(ss->zPos));
  //  pter.drawText(0, 60, "Velocity:");
  //  pter.drawText(0, 80,
  //                "(" + QString::number(ss->towardX) + "," +
  //                    QString::number(ss->towardY) + "," +
  //                    QString::number(ss->towardZ) + ") " +
  //                    QString::number(ss->moveSpeed));
  //  pter.end();
}
