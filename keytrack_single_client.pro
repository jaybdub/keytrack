#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T21:09:27
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keytrack_single_client
TEMPLATE = app


SOURCES += main.cpp\
        keytracksingle.cpp \
    keytrackserial.cpp \
    camerawidget.cpp \
    arucowidget.cpp \
    serialwidget.cpp \
    bluetoothwidget.cpp

HEADERS  += keytracksingle.h \
    keytrackserial.h \
    camerawidget.h \
    arucowidget.h \
    serialwidget.h \
    bluetoothwidget.h

FORMS    += keytracksingle.ui \
    keytrackserial.ui \
    camerawidget.ui \
    arucowidget.ui \
    serialwidget.ui \
    bluetoothwidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../aruco-1.2.4/build/src/release/ -laruco
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../aruco-1.2.4/build/src/debug/ -laruco
else:unix: LIBS += -L$$PWD/../../aruco-1.2.4/build/src/ -laruco

INCLUDEPATH += $$PWD/../../aruco-1.2.4/build/src
DEPENDPATH += $$PWD/../../aruco-1.2.4/build/src

#Include opencv core
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../opt/ros/hydro/lib/release/ -lopencv_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../opt/ros/hydro/lib/debug/ -lopencv_core
else:unix: LIBS += -L$$PWD/../../../../opt/ros/hydro/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../../opt/ros/hydro/include
DEPENDPATH += $$PWD/../../../../opt/ros/hydro/include

#include opencv highgui (for video capture)
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../opt/ros/hydro/lib/release/ -lopencv_highgui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../opt/ros/hydro/lib/debug/ -lopencv_highgui
else:unix: LIBS += -L$$PWD/../../../../opt/ros/hydro/lib/ -lopencv_highgui

INCLUDEPATH += $$PWD/../../../../opt/ros/hydro/include
DEPENDPATH += $$PWD/../../../../opt/ros/hydro/include
