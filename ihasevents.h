#ifndef IHASEVENTS_H
#define IHASEVENTS_H

class QXmlAttributes;
namespace vnews
{
    class Event;
    class IHasEvents
    {
    public:
       // virtual ~IHasEvents() {}
        virtual Event* createEvent(const QXmlAttributes& attributes) = 0;
    };
}

#endif // IHASEVENTS_H
