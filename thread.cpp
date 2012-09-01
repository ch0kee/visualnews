#include "thread.h"
#include "event.h"
#include <QXmlAttributes>
#include <QDebug>

Thread::Thread(QObject* parent)
    : QObject(parent)
{
}

Thread::~Thread()
{
    // események törlése
    Q_FOREACH(Event* e, _events)
    {
        delete e;
    }
    _events.clear();
}

void Thread::addEvent( Event* e )
{
    Q_ASSERT(e != 0);

    if (!_events.empty())
    {
        QObject::connect(_events.back(), SIGNAL(finished()),
                         e, SLOT(start()));
    }
    _events.push_back( e );
}

Event* Thread::createEvent(const QString &name, const QString &param)
{
    if (name == "milestone")
    {

        return milestones_[ param ] = new MilestoneEvent();
    }
    else if (name == "wait")
    {

        return new WaitEvent( param.toInt() );
    }
    else if (name == "goto")
    {

        Q_ASSERT( milestones_.contains(param) );
        return new GotoEvent( milestones_[param] );
    }
    else
    {
        qDebug() << name << "?";
        Q_ASSERT( !"Unknown thread event" );
        return 0;
    }

}

void Thread::start()
{
    if (!_events.empty())
        _events.front()->start();
}

///////////////////////////////////////////////
// WaitEvent
///////////////////////////////////////////////

WaitEvent::WaitEvent(int interval)
    : Event(0), _interval(interval)
{
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SIGNAL(finished()));
}

WaitEvent::~WaitEvent()
{
    timer.stop();
}

void WaitEvent::start()
{
    timer.start(_interval);
}


///////////////////////////////////////////////
// MilestoneEvent
///////////////////////////////////////////////
MilestoneEvent::MilestoneEvent()
    : Event(0)
{

}

void MilestoneEvent::start()
{
    Q_EMIT finished();
}

///////////////////////////////////////////////
// GotoEvent
///////////////////////////////////////////////
GotoEvent::GotoEvent(MilestoneEvent* target)
    : Event(0), target_(target)
{

}

void GotoEvent::start()
{
    target_->start();
}
