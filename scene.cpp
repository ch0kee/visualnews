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
#include "xmlsessionhandler.h"
#include "logger.h"
#include <QtGui/QApplication>
#include <QMessageBox>
#include "exceptions.h"


Scene::Scene()
    : QGraphicsScene(0), _threads(this), _layout(this)
{


//c akkor kell, ha lassú az animáció
    //   setItemIndexMethod( QGraphicsScene::NoIndex );
}

void Scene::setView( QGraphicsView* view)
{
    view->setScene(this);
}

void    Scene::setSession(const QString& sessionFilename)
{
    this->stop();
    fillScene(sessionFilename);
    this->start();
    this->getMainView()->showNormal();
}

void Scene::fillScene(const QString &filename)
{
#if 0
  _lastFilename = filename;
  XmlSessionHandler xmlhandler(this);
  QXmlSimpleReader reader;
  reader.setContentHandler(&xmlhandler);

  QFile sessionfile(filename);
  QXmlInputSource source(&sessionfile);
  if (!reader.parse(source))
    throw Exception<EET_PARSEERROR>("invalid session data");
#endif
}



#if 0
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
#endif
void    Scene::start()
{
    threads().start();
}



void    Scene::stop()
{
    _threads.clear();
    _layout.clear();
    clear();
    LOG( "stopped" );
}

bool ViewKeyboardFilter::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        keyEvent->accept();
        switch (keyEvent->key())
        {
          case Qt::Key_F1:
            _view->showNormal();
            break;
          case Qt::Key_F2:
            _view->showFullScreen();
            break;
          case Qt::Key_F3:
          {//restart
            //this->stop();
           // fillScene(filledFrom);
           // this->start();
          }
            break;
          case Qt::Key_F4:
            QApplication::exit(0);
            break;
          default:
            break;
        }
        return true;
    }
    else
        return QObject::eventFilter(obj,e);
}

ViewKeyboardFilter::ViewKeyboardFilter(QGraphicsView *view)
    : _view(view)
{
    _view->installEventFilter(this);
}
