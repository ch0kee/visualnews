#include "xmlparser.h"
#include "scene.h"
#include "thread.h"
#include "event.h"
#include <QXmlAttributes>
#include "window.h"
#include <QString>
#include "ihasevents.h"
#include "content.h"
#include "logger.h"


bool XmlEventsParser::startElement(const QString &qName, const QXmlAttributes &attributes)
{
    if (qName == "Thread")
    {
        scene()->threads().addThread(new Thread( this->scene() ));
    }
    else if (qName == "Run")
    {
        Thread * t = scene()->threads().last();
        Q_ASSERT( t != 0 );
        QString targetName = attributes.value("Target");

        if (targetName.isNull() || targetName.isEmpty())
        {
            Event* e = t->createEvent(attributes);
            t->addEvent(e);
        }
        else
        {
            SceneObject* o = scene()->layout().sceneObjectByName(targetName);
            Event* e = o->createEvent(attributes);
            t->addEvent(e);
        }

    }
    else
    {
        return false;
    }
    return true;
}

bool XmlEventsParser::endElement(const QString &qName)
{
    if (qName == "Thread" || qName == "Run")
        return true;
    else
        return false;
}

bool XmlLayoutParser::startElement(const QString &qName, const QXmlAttributes &attributes)
{
    if (qName == "Window")
    //@ <WINDOW>
    {
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
        scene()->layout().addWindow(w);

    }
    else if (qName == "Content")
    //@ <CONTENT>
    {
        Content* c = Content::CreateContent(attributes, *scene());
        Q_ASSERT( c );
        c->preload(scene()->layout().lastWindow());
    }
    else
    {
        return false;
    }
    return true;
}

bool XmlLayoutParser::endElement(const QString &qName)
{
    if (qName == "Window" || qName == "Content")
        return true;
    else
        return false;
}
