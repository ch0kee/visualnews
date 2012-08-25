#ifndef IHASGRAPHICSITEM_H
#define IHASGRAPHICSITEM_H

class QGraphicsItem;
class IHasGraphicsItem
{
public:
   // virtual ~IHasGraphicsItem() {}
    virtual QGraphicsItem* graphicsItem() const = 0;
};

#endif // IHASGRAPHICSITEM_H
