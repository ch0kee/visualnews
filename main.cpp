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
#include "visualnewsapplication.h"
bool isLayoutGiven(int argc);
int printUsage(const char* progname);


int main(int argc, char** argv)
{
  if (!isLayoutGiven(argc))
    return printUsage(argv[0]);

  VisualNewsApplication vnapp(argc, argv);

  int ret = 1;
  try
  {
    ret = vnapp.run();
  }
  catch(IException& ex)
  {
    ex.print();
    return 1;
  }

  return ret;
}

bool isLayoutGiven(int argc) { return argc >= 2; }

int printUsage(const char* progname)
{
  std::cout << "-. missing parameters" << std::endl;
  std::cout << "-. usage: " << progname << " LAYOUT-FILE [PARAMÉTEREK]" << std::endl;
  return 1;
}
