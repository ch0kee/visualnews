#ifndef XMLEVENTSPARSER_H
#define XMLEVENTSPARSER_H

#include "xmlparser.h"

namespace vnews
{
    class Thread;
    class Event;
    class XmlEventsParser : public XmlParser
    {
    public:
        XmlEventsParser();
        bool startElement(const QString &qName, const QXmlAttributes &attributes);
        bool endElement(const QString &qName);
    private:
        Thread* currentThread_;
        Event* currentEvent_;
    };
}
#endif // XMLEVENTSPARSER_H
