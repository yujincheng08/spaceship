#include "mainwindow.h"
#include <QMenuBar>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createWidgets();
    setCentralWidget(quickWidget);
    createConnections();
}

void MainWindow::createWidgets()
{
    quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
    quickWidget->setMinimumSize(300, 300);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    fileMenu->addAction(exitAction);
    aboutMenu->addAction(aboutQtAction);
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(aboutMenu);
}

void MainWindow::createConnections()
{
    connect(exitAction, &QAction::triggered, qApp, &QApplication::exit);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}
