#ifndef CONTENT_H
#define CONTENT_H


#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QXmlAttributes>
#include <QRectF>
#include <QPixmap>
#include <QString>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QImage>
#include <QPainter>
#include "window.h"
#include "sceneobject.h"

class Scene;
class QWebPage;
class Content : public SceneObject
{
public:

    virtual ~Content();
    static Content* CreateContent(const QXmlAttributes& attrs, Scene& scene);

    QGraphicsItem* graphicsItem() const{ return graphicsItem_; }

    void    preload(Window* window);
    const QString& name() const { return _name; }
protected:
    Content();

    virtual QGraphicsItem* createGraphicsItem(const QRectF& rect) = 0;
    QString _url;

    QGraphicsItem* graphicsItem_;
        private:
    QString _name;
};


class HtmlContent : public QObject, public Content
{
    Q_OBJECT
public:
    HtmlContent(Scene& scene);
protected:
    QGraphicsItem* createGraphicsItem(const QRectF& rect);


private:
    Scene& _scene;
    QWebPage* _webPage;
};

class ImageContent : public Content
{
protected:
    QGraphicsItem* createGraphicsItem(const QRectF& rect);
};

class TextContent : public Content
{
protected:
    QGraphicsItem* createGraphicsItem(const QRectF& rect);
};




#endif // CONTENT_H
