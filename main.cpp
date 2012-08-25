#include <QtGui/QApplication>
#include "scene.h"
#include <QTextStream>
#include <iostream>
#include <QGraphicsView>
#include "logger.h"
#include <QDir>
#include <QStringList>
#include <algorithm>
#include "exceptions.h"

_Log logger;

bool isLayoutGiven(int argc, char** argv)
{
    return argc >= 2 && QFile::exists(argv[1]);
}
//./vnews [layout-file] [konstansok]
int main(int argc, char** argv)
{
    if (!isLayoutGiven(argc, argv))
        return 1;
    QApplication app(argc, argv);
    QApplication::setOverrideCursor(Qt::BlankCursor);

    Scene       scene;

    int ret = 1;
    try {
        scene.setSession(argv[1]);
        ret = app.exec();
    }
    catch(IException& ex) {
        logger << ex.message().toStdString();
        ret = 1;
    }
    return ret;
}

