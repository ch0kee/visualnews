#ifndef THREAD_H
#define THREAD_H

#include <vector>
#include <QObject>
#include "ihasevents.h"
#include "event.h"
#include <QMap>
#include <QThread>

class MilestoneEvent;
class Event;
class Thread : public QObject, public IHasEvents
{
    Q_OBJECT
public:
    Thread(QObject* parent);
    ~Thread();
    void addEvent( Event* e );
    Event* createEvent(const QXmlAttributes& attributes);
public Q_SLOTS:
    void start();
private:
    std::vector<Event*> _events;
    QMap<QString, MilestoneEvent*> milestones_;
};

class WaitEvent : public Event
{
    Q_OBJECT
public:
    WaitEvent(int interval);
    ~WaitEvent();

public Q_SLOTS:
    void start();
private:
    class WaitingThread : public QThread
    {
        int interval_;
    public:
        WaitingThread(int interval);
        void run();
    } _waitThread;
};

class MilestoneEvent : public Event
{
    Q_OBJECT
public:
    MilestoneEvent();
public Q_SLOTS:
    void start();
};

class GotoEvent : public Event
{
    Q_OBJECT
public:
    GotoEvent(MilestoneEvent* target);
public Q_SLOTS:
    void start();
private:
    MilestoneEvent* target_;
};

#endif // THREAD_H
