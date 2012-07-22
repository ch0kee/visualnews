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
    saxscenehandler.cpp \
    xmlparser.cpp \
    xmleventsparser.cpp \
    xmllayoutparser.cpp \
    thread.cpp \
    event.cpp \
    sceneobject.cpp \
    sceneobjectevents.cpp \
    scenelayouthandler.cpp \
    sceneeventshandler.cpp \
    scenetcpserver.cpp \
    commandadapter.cpp \
    visualnewsapplication.cpp

HEADERS  += \
    window.h \
    programwidget.h \
    content.h \
    logger.h \
    scene.h \
    saxscenehandler.h \
    xmlparser.h \
    xmleventsparser.h \
    xmllayoutparser.h \
    thread.h \
    event.h \
    ihasgraphicsitem.h \
    ihasevents.h \
    sceneobject.h \
    sceneobjectevents.h \
    scenelayouthandler.h \
    sceneeventshandler.h \
    scenetcpserver.h \
    exceptions.h \
    commandadapter.h \
    visualnewsapplication.h

OTHER_FILES += \
    developments.txt \
    test.vnsession \
    visualnews.config
