QT += widgets quickwidgets 3dcore 3drender 3dinput 3dquick 3dlogic qml quick 3dquickextras gamepad datavisualization opengl core gui
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES -= UNICODE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lglut -lGLU -lGL

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mycamera.cpp \
    src/component.cpp \
    src/mylight.cpp \
    src/spaceship.cpp \
    src/planet.cpp \
    src/infosurface.cpp \
    src/scene.cpp \
    src/cameracontroller.cpp

RESOURCES += \
    assets.qrc \

INCLUDEPATH += src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/mainwindow.h \
    src/mycamera.h \
    src/component.h \
    src/mylight.h \
    src/spaceship.h \
    src/planet.h \
    src/infosurface.h \
    src/scene.h \
    src/cameracontroller.h



