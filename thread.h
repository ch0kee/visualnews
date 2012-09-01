#ifndef THREAD_H
#define THREAD_H

#include <vector>
#include <QObject>
#include "event.h"
#include <QMap>
#include <QThread>
#include <QVariant>
#include <QTimer>

class MilestoneEvent;
class Event;
class Thread : public QObject
{
    Q_OBJECT
public:
    Thread(QObject* parent=0);
    ~Thread();
    void addEvent( Event* e );
    Event* createEvent(const QString& name, const QString &param);
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
    QTimer timer;
    int _interval;
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
