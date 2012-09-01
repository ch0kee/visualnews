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
#include "programwidget.h"
#include "session.h"
#include "engine.h"


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

    Session session;
    Session::ReadFromXml(session, argv[1]);

    QGraphicsScene      scene;
    UI::ProgramWidget   view (&scene);
    ViewKeyboardFilter  filter(&view);

    Engine  engine;
    engine.setSession(&session);
    engine.setScene(&scene);
    engine.fillScene();

    engine.startAnimation();
    view.showNormal();

    return app.exec();
}

