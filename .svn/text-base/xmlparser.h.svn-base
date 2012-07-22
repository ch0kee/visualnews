#ifndef XMLPARSER_H
#define XMLPARSER_H

class QString;
class QXmlAttributes;
class Scene;
namespace vnews
{
    class XmlParser
    {
    public:
        void setScene(Scene* s);

        virtual bool startElement(const QString &qName, const QXmlAttributes &attributes) = 0;
        virtual bool endElement(const QString &qName) = 0;
    protected:
        XmlParser();
        Scene* scene();
    private:
        Scene* scene_;

    };
}

#endif // XMLPARSER_H
