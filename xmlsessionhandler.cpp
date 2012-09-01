#include "xmlsessionhandler.h"
#include "logger.h"
#include "scene.h"
#include "window.h"
#include "content.h"
#include "thread.h"
#include "session.h"
#include <QRectF>

bool XmlSessionHandler::startElement(const QString &namespaceURI,
                                   const QString &localName,
                                   const QString &qName,
                                   const QXmlAttributes &attributes)
{
  Q_UNUSED(namespaceURI);
  Q_UNUSED(localName);
  if (qName == "Session")
  {
#if 0
    Q_ASSERT( _scene != 0 );
#endif
  }
  else if (qName == "Layout")
  {
#if 0
    //@ Background Image
    QString bgimage = attributes.value("BackgroundImage");
    _scene->setBackgroundBrush(QBrush(QImage(bgimage)));
    //scene_->setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
    QRectF sgeom(attributes.value("X").toDouble(),
                 attributes.value("Y").toDouble(),
                 attributes.value("Width").toDouble(),
                 attributes.value("Height").toDouble());
    _scene->setSceneRect(sgeom);
#endif
    QString bgimage = attributes.value("BackgroundImage");
    double width = attributes.value("Width").toDouble();
    double height = attributes.value("Height").toDouble();
    _session->setBackgroundImagePath(bgimage);
    _session->setResolution(QSizeF(width, height));
  }
  else if (qName == "Behavior")
  {
  }
  ///////////////
  else if (qName == "Thread")
  {
      _session->addThread();
#if 0
      _scene->threads().addThread(new Thread( _scene ));
#endif
  }
  else if (qName == "Run")
  {
        Session::attributes_t attrs;
        //QString memberName = attributes.value("Member");
        QString member;
        for(int i = 0; i < attributes.count(); ++i)
        {
            QString name = attributes.qName(i);
            QString value = attributes.value(i);
            if (name == "Member")
                member = value;
            else
                attrs[name] = value;
        }
        _session->addEvent(member, attrs);

#if 0
      Thread * t = _scene->threads().last();
      Q_ASSERT( t != 0 );
      QString targetName = attributes.value("Target");

      if (targetName.isNull() || targetName.isEmpty())
      {
          Event* e = t->createEvent(attributes);
          t->addEvent(e);
      }
      else
      {
          SceneObject* o = _scene->layout().sceneObjectByName(targetName);
          Event* e = o->createEvent(attributes);
          t->addEvent(e);
      }
#endif
  }

///
  else if (qName == "Window")
  {
      QString name = attributes.value("Name");
      QRectF geom(attributes.value("X").toDouble(),
                   attributes.value("Y").toDouble(),
                   attributes.value("Width").toDouble(),
                   attributes.value("Height").toDouble());
      double zlevel = attributes.value("ZLevel").toDouble();
      bool hasborder = attributes.value("Border").toInt();
      _session->addWindow(name, geom, zlevel, hasborder);
#if 0
      //@ Identifier
      QString wid = attributes.value("Name");
      Window* w = new Window(wid);
//        w->_name = wid;
      //@ Geometry
      QRectF wgeom(attributes.value("X").toDouble(),
                   attributes.value("Y").toDouble(),
                   attributes.value("Width").toDouble(),
                   attributes.value("Height").toDouble());
      w->setRect( wgeom );
      //@ Z-Level
      double zlevel = attributes.value("ZLevel").toDouble();
      w->setZValue( zlevel );
      //@ Has Border
      //bool hasborder = (attributes.value("Border").toInt() != 0);
      //if (hasborder)
      //    w->addBorder();
      _scene->layout().addWindow(w);
#endif
  }
  else if (qName == "Content")
  {
      QString name = attributes.value("Name");
      QString type = attributes.value("Type");
      QString url = attributes.value("Url");
      _session->addContent(name, type, url);
#if 0
      Content* c = Content::CreateContent(attributes, _scene);
      Q_ASSERT( c );
      c->preload(_scene->layout().lastWindow());
#endif
  }

  ///////////////

  else
  {
    return false;
  }
  return true;
}

bool XmlSessionHandler::endElement(const QString &namespaceURI,
                                 const QString &localName,
                                 const QString &qName)
{
    Q_UNUSED(namespaceURI);
    Q_UNUSED(localName);

    if (qName == "Session")
    {
    }
    else if (qName == "Layout")
    {
    }
    else if (qName == "Behavior")
    {
    }
    else if (qName == "Thread" || qName == "Run")
    {

    }
    else if (qName == "Window" || qName == "Content")
    {

    }
    else
    {
        return false;
    }

    return true;
}
