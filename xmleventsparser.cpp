#include "xmleventsparser.h"
#include "scene.h"
#include "thread.h"
#include "event.h"
#include <QXmlAttributes>
#include "window.h"
#include <QString>
#include "ihasevents.h"
#include "content.h"
#include "logger.h"

using namespace vnews;

XmlEventsParser::XmlEventsParser()
    : currentThread_(0), currentEvent_(0)
{
}

bool XmlEventsParser::startElement(const QString &qName, const QXmlAttributes &attributes)
{
    if (qName == "Thread")
    {
        Q_ASSERT(currentThread_ == 0 );
        currentThread_ = new Thread( this->scene() );

    }
    else if (qName == "Run")
    {
        Q_ASSERT( currentThread_ != 0 );
        Q_ASSERT( currentEvent_ == 0 );
        QString contentName = attributes.value("Content");
        QString windowName = attributes.value("Window");
        IHasEvents* eventHost = currentThread_;
        if (!windowName .isEmpty())
        {
            Window* w = scene()->layout().windowByName(windowName);
            if (!contentName.isEmpty())
            {
                Content* c = w->contentByName(contentName);
                eventHost = c;
            }
            else
            {
                eventHost = w;
            }
        }

        currentEvent_ = eventHost->createEvent(attributes);
        Q_ASSERT(currentEvent_);
    }
    else
    {
        return false;
    }
    return true;
}

bool XmlEventsParser::endElement(const QString &qName)
{
    if (qName == "Thread")
    {
        Q_ASSERT( currentThread_ != 0 );
        scene()->threads().addThread(currentThread_);
        currentThread_ = 0;
    }
    else if (qName == "Run")
    {
        Q_ASSERT( currentThread_ != 0 );
        Q_ASSERT( currentEvent_ != 0);
        currentThread_->addEvent(currentEvent_);
        currentEvent_ = 0;
    }
    else
    {
        return false;
    }
    return true;
}
