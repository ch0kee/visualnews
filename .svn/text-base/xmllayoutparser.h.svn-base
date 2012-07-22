#ifndef XMLLAYOUTPARSER_H
#define XMLLAYOUTPARSER_H

#include "xmlparser.h"

namespace vnews
{
    class Window;
    class Content;
    class XmlLayoutParser : public XmlParser
    {
    public:
        XmlLayoutParser();
        bool startElement(const QString &qName, const QXmlAttributes &attributes);
        bool endElement(const QString &qName);
    private:
        Window* currentWindow_;
        Content* currentContent_;
    };
}
#endif // XMLLAYOUTPARSER_H
