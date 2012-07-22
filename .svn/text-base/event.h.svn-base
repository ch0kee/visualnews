#ifndef EVENT_H
#define EVENT_H

#include <QObject>

namespace vnews
{
    class Event : public QObject
    {
        Q_OBJECT
    public:
        Event(QObject* parent);
        virtual ~Event();
    Q_SIGNALS:
        void finished();
    public Q_SLOTS:
        virtual void start() = 0;
    };
}

#endif // EVENT_H
