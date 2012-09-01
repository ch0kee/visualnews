#ifndef SAXSCENEHANDLER_H
#define SAXSCENEHANDLER_H

#include <QXmlDefaultHandler>

class Scene;
class XmlParser;
class Session;
class XmlSessionHandler : public QXmlDefaultHandler
{
public:
    XmlSessionHandler(Session* s)
        : _session(s) {}
    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &attributes);

    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
private:
    Session* _session;
};

#endif // SAXSCENEHANDLER_H
