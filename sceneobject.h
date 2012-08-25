#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "ihasgraphicsitem.h"
#include "ihasevents.h"

class SceneObject : public IHasGraphicsItem
{
public:
    SceneObject();
    virtual ~SceneObject() {};

    virtual Event* createEvent(const QXmlAttributes& attributes);
};

#endif // SCENEOBJECT_H
