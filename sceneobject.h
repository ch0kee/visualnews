#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "ihasgraphicsitem.h"

class QString;
class Event;
class SceneObject : public IHasGraphicsItem
{
public:
    SceneObject();
    virtual ~SceneObject() {};

    Event* createEvent(const QString &name);
};

#endif // SCENEOBJECT_H
