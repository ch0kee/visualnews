#include "sceneobject.h"
#include <QXmlAttributes>
#include "sceneobjectevents.h"

SceneObject::SceneObject()
{
}

Event* SceneObject::createEvent(const QXmlAttributes& attributes)
{
    Event* event = 0;

    QString member = attributes.value("Member");
    if (member == "fadein")
    {
        event = new Events::FadeInSceneObject(this);
    }
    else if (member == "fadeout")
    {
        event = new Events::FadeOutSceneObject(this);
    }
    else if (member == "show")
    {
        event = new Events::ShowSceneObject(this);
    }
    else if (member == "hide")
    {
        event = new Events::HideSceneObject(this);
    }
    else if (member == "scroll")
    {
        event = new Events::ScrollSceneObject(this);
    }
    else
    {
        Q_ASSERT(!"Unknown content event");
    }

    return event;
}

