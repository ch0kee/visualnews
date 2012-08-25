#include "scene.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include "content.h"
#include <QTimeLine>
#include <QGraphicsItemAnimation>

#include <QKeyEvent>
#include <algorithm>
#include "programwidget.h"
#include <iostream>
#include "thread.h"
#include "window.h"
#include "saxscenehandler.h"
#include "logger.h"
#include <QtGui/QApplication>
#include <QMessageBox>
#include "exceptions.h"
#include "visualnewsapplication.h"


Scene::Scene()
    : QGraphicsScene(0), _threads(this), _layout(this)
{
  new UI::ProgramWidget(this);

//c akkor kell, ha lassú az animáció
//   setItemIndexMethod( QGraphicsScene::NoIndex );
}

void    Scene::setSession(const QString& sessionFilename)
{
    this->stop();
    fillScene(sessionFilename);
    this->start();
    this->getMainView()->showNormal();
}

//QString filledFrom;
void Scene::fillScene(const QString &filename)
{
  _lastFilename = filename;
  LOG( "filling scene");
  SAXSceneHandler sceneHandler(this);
  QXmlSimpleReader reader;
  reader.setContentHandler(&sceneHandler);

  LOG( "opening file");
  QFile sessionfile(filename);

/*    if (!sessionfile.isOpen())
  //    throw Exception<EET_IOERROR>("can't open session file");

    if (!sessionfile.isReadable())
      throw Exception<EET_IOERROR>("can't read session file");
*/
  QXmlInputSource source(&sessionfile);
  LOG( "parsing...");
  if (!reader.parse(source))
    throw Exception<EET_PARSEERROR>("invalid session data");

  LOG( "parse done" );

  //filledFrom = filename;
}




void    Scene::keyPressEvent ( QKeyEvent * keyEvent )
{
  keyEvent->accept();
  switch (keyEvent->key())
  {
    case Qt::Key_F1:
      getMainView()->showNormal();
      break;
    case Qt::Key_F2:
      getMainView()->showFullScreen();
      break;
    case Qt::Key_F3:
    {//restart
      //this->stop();
     // fillScene(filledFrom);
     // this->start();
    }
      break;
    case Qt::Key_F4:
      this->stop();
      QApplication::exit(0);
      break;
    case Qt::Key_F5:
      this->stop();
    default:
      keyEvent->ignore();
      break;
  }

  QGraphicsScene::keyPressEvent(keyEvent);
}

void    Scene::start()
{
  LOG( "starting threads");
  threads().start();
  LOG( "showing fullscreen");
}



void    Scene::stop()
{
  //stop threads
  _threads.clear();
  _layout.clear();
  clear();
  LOG( "stopped" );

}
