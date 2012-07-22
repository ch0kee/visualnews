#ifndef VISUALNEWSAPPLICATION_H
#define VISUALNEWSAPPLICATION_H

#include <QApplication>
#include <QStringList>
#include "scene.h"


class VisualNewsApplication : public QApplication
{
public:
  VisualNewsApplication(int argc, char** argv);

  int  run();
private:
  Scene       _scene;
  QStringList _arguments;
};

#endif // VISUALNEWSAPPLICATION_H
