#include "saxscenehandler.h"
#include "logger.h"
#include "scene.h"
#include "window.h"
#include "content.h"
#include "xmllayoutparser.h"
#include "xmleventsparser.h"

using namespace vnews;

SAXSceneHandler::SAXSceneHandler(Scene* s)
    : scene_(s), xmlParser_(0)
{
}


bool SAXSceneHandler::startElement(const QString &namespaceURI,
                                   const QString &localName,
                                   const QString &qName,
                                   const QXmlAttributes &attributes)
{
  Q_UNUSED(namespaceURI);
  Q_UNUSED(localName);
  if (xmlParser_)
  {
    return xmlParser_->startElement(qName, attributes);
  }
  else if (qName == "Scene")
  //@ <SCENE>
  {
    Q_ASSERT( scene_ != 0 );
    //kezdődik
  }
  else if (qName == "Layout")
  //@ <LAYOUT>
  {
    Q_ASSERT( xmlParser_ == 0 );
    xmlParser_ = new XmlLayoutParser();
    xmlParser_->setScene(scene_);


    //@ Background Image
    QString bgimage = attributes.value("BackgroundImage");
    scene_->setBackgroundBrush(QBrush(QImage(bgimage)));
    //scene_->setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
    //@ Geometry
    QRectF sgeom(attributes.value("X").toDouble(),
                 attributes.value("Y").toDouble(),
                 attributes.value("Width").toDouble(),
                 attributes.value("Height").toDouble());
    scene_->setSceneRect(sgeom);
  }
  else if (qName == "Events")
  //@ <EVENTS>
  {
    Q_ASSERT( xmlParser_ == 0 );
    xmlParser_ = new XmlEventsParser();
    xmlParser_->setScene(scene_);
  }
  else
  {
    return false;
  }
  return true;
}

bool SAXSceneHandler::endElement(const QString &namespaceURI,
                                 const QString &localName,
                                 const QString &qName)
{
  Q_UNUSED(namespaceURI);
  Q_UNUSED(localName);

  if (xmlParser_)
  {
    if (qName == "Layout")
    //@ </LAYOUT>
    {
      delete xmlParser_;
      xmlParser_ = 0;
    }
    else if (qName == "Events")
    //@ </EVENTS>
    {
      delete xmlParser_;
      xmlParser_ = 0;
    }
    else
    {
      return xmlParser_->endElement(qName);
    }
  }
  else if (qName == "Scene")
  //@ </SCENE>
  {
      //GYŐZELEM ?
  }
  else
  {
    return false;
  }
  return true;
}