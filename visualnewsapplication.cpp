#include "visualnewsapplication.h"
#include <algorithm>
#include <QGraphicsView>
#include <QDebug>
#include <QDir>

VisualNewsApplication::VisualNewsApplication(int argc, char** argv)
    : QApplication(argc, argv)
  {
     std::for_each(argv, argv+argc, [this](char* arg) { _arguments.append(arg); } );

QApplication::setOverrideCursor(Qt::BlankCursor);

}

int  VisualNewsApplication::run()
  {
    // current path
    qDebug() << "current path=" << QDir::currentPath();

    // setting session by cmdarg
    _scene.setSession(_arguments[1]);
    return exec();
  }
