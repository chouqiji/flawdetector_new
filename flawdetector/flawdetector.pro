#-------------------------------------------------
#
# Project created by QtCreator 2018-09-29T21:08:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlawDetector
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
        inc/

SOURCES += \
        src/main.cpp \
        src/desktop.cpp \
    src/globalmanager.cpp \
    src/component/arginspector.cpp \
    src/devicearg/devicearg_impl.cpp

HEADERS += \
        inc/desktop.h \
    inc/globalmanager.h \
    inc/devicearg.h \
    inc/private/devicearg_impl.h \
    inc/arginspector.h \
    inc/devicearg/viewport.h \
    inc/devicearg/editport.h \
    inc/devicearg/devicearg.h

QMAKE_CXXFLAGS -= -std=gnu++11 -std=std++11
QMAKE_CXXFLAGS *= -std=gnu++17

TRANSLATIONS += \
    zh_cn.ts
