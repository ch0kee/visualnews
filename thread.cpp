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


Event* Thread::createEvent(const QXmlAttributes& attributes)
{
    QString function = attributes.value("Member");
    if (function == "milestone")
    {
        Q_ASSERT( attributes.count() == 2 );
        Q_ASSERT( attributes.index("Member") != -1 );
        Q_ASSERT( attributes.index("Id") != -1 );

        return milestones_[ attributes.value("Id") ] = new MilestoneEvent();
    }
    else if (function == "wait")
    {
        Q_ASSERT( attributes.count() == 2 );
        Q_ASSERT( attributes.index("Member") != -1 );
        Q_ASSERT( attributes.index("Interval") != -1 );

        return new WaitEvent( attributes.value("Interval").toInt() );
    }
    else if (function == "goto")
    {
        Q_ASSERT( attributes.count() == 2 );
        Q_ASSERT( attributes.index("Member") != -1 );
        Q_ASSERT( attributes.index("Address") != -1 );

        Q_ASSERT( milestones_.contains(attributes.value("Address")) );
        return new GotoEvent( milestones_[attributes.value("Address")] );
    }
    else
    {
        qDebug() << function << "?";
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
    : Event(0), _waitThread(interval)
{
    QObject::connect(&_waitThread, SIGNAL(finished()),
                     this, SIGNAL(finished()));
}

WaitEvent::~WaitEvent()
{
    _waitThread.terminate();
    _waitThread.wait();
}

void WaitEvent::start()
{
    _waitThread.start();
}


WaitEvent::WaitingThread::WaitingThread(int interval)
    : interval_(interval)
{
}


void WaitEvent::WaitingThread::run()
{
    msleep(interval_);
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
