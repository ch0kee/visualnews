#include "sceneobjectevents.h"
#include <QTimeLine>
#include "ihasgraphicsitem.h"
#include <QGraphicsItem>

const int FADE_DURATION = 1000;

using namespace Events;

ShowSceneObject::ShowSceneObject(IHasGraphicsItem* sceneObject)
    : Event(0), sceneObject_(sceneObject)
{
}

ShowSceneObject::~ShowSceneObject()
{

}

void ShowSceneObject::start()
{
    sceneObject_->graphicsItem()->setVisible( true );
    Q_EMIT finished();
}

HideSceneObject::HideSceneObject(IHasGraphicsItem* sceneObject)
    : Event(0), sceneObject_(sceneObject)
{
}

HideSceneObject::~HideSceneObject()
{

}


void HideSceneObject::start()
{
    sceneObject_->graphicsItem()->setVisible( false );
    Q_EMIT finished();
}

FadeInSceneObject::FadeInSceneObject(IHasGraphicsItem* sceneObject)
    : Event(0), _sceneObject(sceneObject), _timeLine(0)
{
    _timeLine = new QTimeLine(FADE_DURATION, this);
    _timeLine->setFrameRange(0, 100);

    _animation = new FadeInAnimation(this);
    _animation->setItem(_sceneObject->graphicsItem());
    _animation->setTimeLine(_timeLine);

    QObject::connect(_timeLine, SIGNAL(finished()),
                     this, SIGNAL(finished()));
}

FadeInSceneObject::~FadeInSceneObject()
{
    _timeLine->stop();
    delete _animation;
    delete _timeLine;
}

void FadeInSceneObject::start()
{
    _sceneObject->graphicsItem()->setOpacity(0.0);
    _sceneObject->graphicsItem()->setVisible(true);
    _timeLine->start();
}

FadeOutSceneObject::FadeOutSceneObject(IHasGraphicsItem* sceneObject)
    : Event(0), _sceneObject(sceneObject), _timeLine(0)
{
    _timeLine = new QTimeLine(FADE_DURATION, this);
    _timeLine->setFrameRange(0, 100);

    _animation = new FadeOutAnimation(this);
    _animation->setItem(_sceneObject->graphicsItem());
    _animation->setTimeLine(_timeLine);

    QObject::connect(_timeLine, SIGNAL(finished()),
                     this, SLOT(beforeFinished()));
}

FadeOutSceneObject::~FadeOutSceneObject()
{
    _timeLine->stop();
    delete _animation;
    delete _timeLine;
}


void FadeOutSceneObject::start()
{
    _timeLine->start();
}

void FadeOutSceneObject::beforeFinished()
{
    _sceneObject->graphicsItem()->setVisible(false);
    Q_EMIT finished();
}


FadeInSceneObject::FadeInAnimation::FadeInAnimation(QObject* parent)
    : QGraphicsItemAnimation(parent)
{
}
void FadeInSceneObject::FadeInAnimation::beforeAnimationStep( qreal step )
{
    this->item()->setOpacity(step);
    QGraphicsItemAnimation::beforeAnimationStep(step);
}


FadeOutSceneObject::FadeOutAnimation::FadeOutAnimation(QObject* parent)
    : QGraphicsItemAnimation(parent)
{
}
void FadeOutSceneObject::FadeOutAnimation::beforeAnimationStep( qreal step )
{
    this->item()->setOpacity(1.0 - step);
    QGraphicsItemAnimation::beforeAnimationStep(step);
}

ScrollSceneObject::ScrollSceneObject(IHasGraphicsItem *sceneObject)
    : Event(0), _sceneObject(sceneObject), _animation(0), _timeLine(0)
{
    QRectF parentrect = _sceneObject->graphicsItem()->parentItem()->boundingRect();
    QRectF contentrect = _sceneObject->graphicsItem()->boundingRect();
    _animation = new QGraphicsItemAnimation();
    _animation->setPosAt(0., QPointF(parentrect.width(), 0));
    _animation->setPosAt(1., QPointF(-contentrect.width(),0));
    _animation->setItem( _sceneObject->graphicsItem() );
    //teszt: contentwidth=2027 ,50000 ms alatt folyamatos
    _timeLine = new QTimeLine(contentrect.width()*30, this);
    _timeLine->setFrameRange(0, 100);
    _timeLine->setCurveShape( QTimeLine::LinearCurve );
    _animation->setTimeLine(_timeLine);

    QObject::connect(_timeLine, SIGNAL(finished()),
                     this, SIGNAL(finished()));
}

ScrollSceneObject::~ScrollSceneObject()
{
    _timeLine->stop();
    delete _animation;
    delete _timeLine;
}

void ScrollSceneObject::start()
{
    _timeLine->start();
}
