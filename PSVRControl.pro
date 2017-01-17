#-------------------------------------------------
#
# Project created by QtCreator 2017-01-08T17:42:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PSVRControl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
        psvrapi.cpp \
    helpers.cpp

HEADERS  += mainwindow.h \
        psvrapi.h \
    helpers.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

unix|win32: LIBS += -L$$PWD/libusb/lib/msvc_x64/ -llibusb

INCLUDEPATH += $$PWD/libusb/include
DEPENDPATH += $$PWD/libusb/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libusb/lib/msvc_x64/libusb.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/libusb/lib/msvc_x64/liblibusb.a
