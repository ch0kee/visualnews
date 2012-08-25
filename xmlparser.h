#ifndef XMLPARSER_H
#define XMLPARSER_H

class QString;
class QXmlAttributes;
class Scene;
class Window;
class Content;
class Thread;
class Event;

class XmlParser
{
public:
    void setScene(Scene* s) { scene_ = s; }

    virtual bool startElement(const QString &qName, const QXmlAttributes &attributes) = 0;
    virtual bool endElement(const QString &qName) = 0;
    virtual ~XmlParser() {}
protected:
    XmlParser() : scene_(0) {}
    Scene* scene() { return scene_; }
private:
    Scene* scene_;

};

class XmlLayoutParser : public XmlParser
{
public:
    XmlLayoutParser() {}
    bool startElement(const QString &qName, const QXmlAttributes &attributes);
    bool endElement(const QString &qName);
};

class XmlEventsParser : public XmlParser
{
public:
    XmlEventsParser() {}
    bool startElement(const QString &qName, const QXmlAttributes &attributes);
    bool endElement(const QString &qName);
};
#endif // XMLPARSER_H
