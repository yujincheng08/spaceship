#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>
#include <QMenu>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QQuickWidget *quickWidget = new QQuickWidget(this);
    QMenu *fileMenu = new QMenu(tr("File"), this);
    QMenu *aboutMenu = new QMenu(tr("About"), this);
    QAction *exitAction = new QAction(tr("Exit"), this);
    QAction *aboutQtAction = new QAction(tr("About Qt"), this);

    void createWidgets();
    void createConnections();
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINWINDOW_H
