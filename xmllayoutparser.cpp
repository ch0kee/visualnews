#include <QXmlAttributes>

#include "xmllayoutparser.h"
#include "window.h"
#include "content.h"
#include "scene.h"

using namespace vnews;

XmlLayoutParser::XmlLayoutParser()
    : currentWindow_(0), currentContent_(0)
{
}

bool XmlLayoutParser::startElement(const QString &qName, const QXmlAttributes &attributes)
{
    if (qName == "Window")
    //@ <WINDOW>
    {
        Q_ASSERT( currentWindow_ == 0 );
        //nem stabil az ablakban ablak

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
        currentWindow_ = w;
    }
    else if (qName == "Content")
    //@ <CONTENT>
    {
        Q_ASSERT( currentWindow_ != 0 );

        Q_ASSERT( currentContent_ == 0 );
        currentContent_ = Content::CreateContent(attributes, *scene());
        Q_ASSERT( currentContent_ );
    }
    else
    {
        return false;
    }
    return true;
}

bool XmlLayoutParser::endElement(const QString &qName)
{
    if (qName == "Window")
    //@ </WINDOW>
    {
        Q_ASSERT( currentWindow_ != 0 );
        scene()->layout().addWindow(currentWindow_);
        currentWindow_ = 0;
    }
    else if (qName == "Content")
    //@ </CONTENT>
    {
        Q_ASSERT( currentWindow_ != 0 );
        Q_ASSERT( currentContent_ != 0 );
        currentContent_->preload(currentWindow_);
        currentContent_ = 0;
    }
    else
    {
        return false;
    }
    return true;
}
