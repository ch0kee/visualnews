#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "ihasgraphicsitem.h"
#include "ihasevents.h"

namespace vnews
{
    class SceneObject : public IHasGraphicsItem, public IHasEvents
    {
    public:
        SceneObject();

        virtual Event* createEvent(const QXmlAttributes& attributes);
    };
}

#endif // SCENEOBJECT_H
