#include <QApplication>
#include <mainwindow.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_EnableHighDpiScaling);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
