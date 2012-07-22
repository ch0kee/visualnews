#include "window.h"
#include <QPainter>
#include <QGraphicsLineItem>
#include <QPointF>
#include "content.h"
#include <QLinearGradient>
#include <QGraphicsPixmapItem>
#include <QXmlAttributes>
#include <QGraphicsScene>

const float BORDER = 3.f;

using namespace vnews;

Window::Window(const QString& name)
    : _name(name)
{
  contentGroup_ = new ContentGroup();
  contentGroup_->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
  contentGroup_->setVisible(false);
}

Window::~Window()
{
  contentGroup_->scene()->destroyItemGroup(contentGroup_);
  Q_FOREACH(Content* c, contents_)
  {
    delete c;
  }
}

Content* Window::contentByName(QString name)
{
  for(size_t i = 0; i < contents_.size(); ++i)
  {
    if (contents_[i]->name() == name)
      return contents_[i];
  }
  return 0;
}

/*
void    Window::addBorder()
{
    QPen linepen(QBrush(QColor(0,0,200)), BORDER);

    QLineF topline(0., 0., _rect.width(), 0);
    QLineF bottomline(0., _rect.height(), _rect.width(), _rect.height());
    QLineF leftline(0., 0, 0, _rect.height());
    QLineF rightline(_rect.width(), 0, _rect.width(), _rect.height());
    QGraphicsLineItem* itm = new QGraphicsLineItem(topline, this);
    itm->setPen(linepen);
    itm->setZValue(1.);
    this->addToGroup(itm);

    itm = new QGraphicsLineItem(bottomline, this);
    itm->setPen(linepen);
    itm->setZValue(1.);
    this->addToGroup(itm);

    itm = new QGraphicsLineItem(leftline, this);
    itm->setPen(linepen);
    itm->setZValue(1.);
    this->addToGroup(itm);

    itm = new QGraphicsLineItem(rightline, this);
    itm->setPen(linepen);
    itm->setZValue(1.);
    this->addToGroup(itm);
}
*/

void Window::addContent(Content* content)
{
  contents_.push_back(content);
  content->graphicsItem()->setParentItem( contentGroup_ );
  contentGroup_->addToGroup(content->graphicsItem());
}

void Window::setRect(const QRectF& rect)
{
  contentGroup_->rect_.setCoords(0., 0., rect.width(), rect.height());

  const QColor WINDOW_COLOR_FROM(0,50,180, 230);
  const QColor WINDOW_COLOR_TO(180,180,0, 230);
  const QPointF from( contentGroup_->rect_.left()+contentGroup_->rect_.width()/2.,
                      contentGroup_->rect_.bottom() );
  const QPointF to( from.x(), contentGroup_->rect_.top() );

  QLinearGradient gradient(from, to);
  gradient.setColorAt(0., WINDOW_COLOR_FROM);
  gradient.setColorAt(1., WINDOW_COLOR_TO);

  //contentGroup_->rect_ = rect;
  contentGroup_->bgGradient_ = QBrush(gradient);

  contentGroup_->setPos( rect.topLeft() );
}

void Window::setZValue(double z)
{
  contentGroup_->setZValue(z);
}

QRectF  Window::childrenBoundingRect() const
{
  QRectF cbr(contentGroup_->pos(), contentGroup_->rect_.size());
  //cbr.adjust(10,10,-10,-10);
  return cbr;
}

void ContentGroup::paint(QPainter* p,
                   const QStyleOptionGraphicsItem* const option,
                   QWidget* w)
{
  Q_UNUSED(option);
  Q_UNUSED(w);
  p->fillRect(rect_, bgGradient_);
}
