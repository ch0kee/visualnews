#ifndef SAXSCENEHANDLER_H
#define SAXSCENEHANDLER_H

#include <QXmlDefaultHandler>

class Scene;
class XmlParser;

class SAXSceneHandler : public QXmlDefaultHandler
{
public:
    SAXSceneHandler(Scene* s);
    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &attributes);

    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
private:
    Scene* scene_;
    XmlParser* xmlParser_;
};

#endif // SAXSCENEHANDLER_H
