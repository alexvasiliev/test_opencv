#-------------------------------------------------
#
# Project created by QtCreator 2014-08-07T12:50:37
#
#-------------------------------------------------


CONFIG += QT_USE_NATIVE_WINDOWS=1
QT       += core
QT       += gui
QT += widgets
QT += opengl
QT += network

TARGET = practice
CONFIG   += console thread X11
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += /opt/opencv/include
LIBS += -L/opt/opencv/lib
#LIBS += `pkg-config opencv –cflags –libs`
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree


HEADERS += \
    Thread/Thread.hpp \
    Thread/ThreadImpl.h \
    MainWindow.h \
    opengl/QtOpenCVViewerGl.h \
    CVCaptureThread.h \
    utils.h \
    opengl/GLXRenderer.h \
    opengl/OverlayWidget.h \
    AnalyticThread.h \
    ptzcontrolthread.h

SOURCES += main.cpp \
    Thread/ThreadImpl.cpp \
    MainWindow.cpp \
    opengl/QtOpenCVViewerGl.cpp \
    CVCaptureThread.cpp \
    opengl/GLXRenderer.cpp \
    opengl/OverlayWidget.cpp \
    AnalyticThread.cpp \
    ptzcontrolthread.cpp
