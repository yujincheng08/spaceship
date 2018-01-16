#include "mainwindow.h"
#include <Qt3DExtras/QForwardRenderer>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  initInfoSurface();
  initScene();
  //  scene->addObserver(infoSurface);
  setGeometry(8, 30, 1360, 768);
  setCentralWidget(container);
  container->setFocus();
  // overlayWidget->setBackgroundWidget(container);
}

MainWindow::~MainWindow() {
  // delete overlayWidget;
  //  makeCurrent();
  //  for (int i = 0; i < components.length(); i++)
  //    delete components.at(i);
  //  delete cursorTimer;
  //  doneCurrent();
}

void MainWindow::initScene(const QColor &clearColor) {
  scene->defaultFrameGraph()->setClearColor(clearColor);
  container->setMinimumSize(QSize(1360, 768));
  container->setMaximumSize(scene->screen()->size());
}

void MainWindow::initInfoSurface() { infoSurface->setBackgroundWidget(this); }
