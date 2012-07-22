#include "sceneobject.h"
#include <QXmlAttributes>
#include "sceneobjectevents.h"

vnews::SceneObject::SceneObject()
{
}

vnews::Event* vnews::SceneObject::createEvent(const QXmlAttributes& attributes)
{
    vnews::Event* event = 0;

    QString member = attributes.value("Member");
    if (member == "fadein")
    {
        event = new vnews::Events::FadeInSceneObject(this);
    }
    else if (member == "fadeout")
    {
        event = new vnews::Events::FadeOutSceneObject(this);
    }
    else if (member == "show")
    {
        event = new vnews::Events::ShowSceneObject(this);
    }
    else if (member == "hide")
    {
        event = new vnews::Events::HideSceneObject(this);
    }
    else if (member == "scroll")
    {
        event = new vnews::Events::ScrollSceneObject(this);
    }
    else
    {
        Q_ASSERT(!"Unknown content event");
    }

    return event;
}

