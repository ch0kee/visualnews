#ifndef WINDOW_H
#define WINDOW_H

#include <QList>
#include <QRectF>
#include <QString>
#include <QBrush>
#include "sceneobject.h"
#include <vector>
#include <QGraphicsItemGroup>

class QGraphicsPixmapItem;
class QGraphicsItem;
namespace vnews
{

    class ContentGroup : public QGraphicsItemGroup
    {
    public:
        void    paint(QPainter* p,
                      const QStyleOptionGraphicsItem* const option,
                      QWidget* w);
        QRectF boundingRect () const { return rect_; }
        QRectF rect_;
        QBrush bgGradient_;
    private:
    };

    class Content;
    class Window : public SceneObject
    {
    public:
        Window(const QString& name);
        ~Window();

        QGraphicsItem* graphicsItem() const { return contentGroup_; }
        void    addContent(Content* content);
        void    setRect(const QRectF& rect);
        void    setZValue(double z);
        QRectF  childrenBoundingRect() const;
        Content* contentByName(QString name);
        const QString& name() const { return _name; }
    private:
        QString _name;
        std::vector<Content*> contents_;
        ContentGroup* contentGroup_;
    };


}

#endif // WINDOW_H
