#-------------------------------------------------
#
# Project created by QtCreator 2011-01-17T18:04:18
#
#-------------------------------------------------

QT       += core gui opengl webkit xml network

TARGET = visualnews
TEMPLATE = app

DEFINES += QUAZIP_STATIC

QMAKE_CXXFLAGS += -std=c++0x

include(../quazip/quazip.pri)

SOURCES += \
    window.cpp \
    programwidget.cpp \
    main.cpp \
    content.cpp \
    scene.cpp \
    thread.cpp \
    event.cpp \
    sceneobject.cpp \
    sceneobjectevents.cpp \
    scenelayouthandler.cpp \
    sceneeventshandler.cpp \
    xmlsessionhandler.cpp \
    session.cpp \
    engine.cpp

HEADERS  += \
    window.h \
    programwidget.h \
    content.h \
    logger.h \
    scene.h \
    thread.h \
    event.h \
    ihasgraphicsitem.h \
    sceneobject.h \
    sceneobjectevents.h \
    scenelayouthandler.h \
    sceneeventshandler.h \
    exceptions.h \
    xmlsessionhandler.h \
    session.h \
    engine.h

OTHER_FILES += \
    developments.txt \
    test.vnsession \
    visualnews.config
