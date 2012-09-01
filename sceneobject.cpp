#include "sceneobject.h"
#include <QXmlAttributes>
#include "sceneobjectevents.h"

SceneObject::SceneObject()
{
}

Event* SceneObject::createEvent(const QString& name)
{
    Event* event = 0;

    if (name == "fadein")
    {
        event = new Events::FadeInSceneObject(this);
    }
    else if (name == "fadeout")
    {
        event = new Events::FadeOutSceneObject(this);
    }
    else if (name == "show")
    {
        event = new Events::ShowSceneObject(this);
    }
    else if (name == "hide")
    {
        event = new Events::HideSceneObject(this);
    }
    else if (name == "scroll")
    {
        event = new Events::ScrollSceneObject(this);
    }
    else
    {
        Q_ASSERT(!"Unknown content event");
    }

    return event;
}

