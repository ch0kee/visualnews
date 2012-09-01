#include "scenelayouthandler.h"
#include "window.h"
#include "content.h"
#include "scene.h"

SceneLayoutHandler::SceneLayoutHandler(Scene* s)
    : _scene(s)
{
}

void    SceneLayoutHandler::clear()
{
    Q_FOREACH(Window* w, layoutWindows_)
    {
        delete w;
    }
    layoutWindows_.clear();
}

Window* SceneLayoutHandler::windowByName(const QString& name)
{
    for(size_t i = 0; i < layoutWindows_.size(); ++i)
    {
        if (layoutWindows_[i]->name() == name)
            return layoutWindows_[i];
    }
    return 0;
}

Content *SceneLayoutHandler::contentByName(const QString& name)
{
    for(size_t i = 0; i < layoutWindows_.size(); ++i)
    {
        Content *c = layoutWindows_[i]->contentByName(name);
        if (c)
            return c;
    }
    return 0;
}

#if 0
void SceneLayoutHandler::addWindow(Window* window)
{
    layoutWindows_.push_back(window);
    _scene->addItem( window->graphicsItem() );
    window->graphicsItem()->setVisible(true);
}
#endif

SceneObject *SceneLayoutHandler::sceneObjectByName(const QString &name)
{
    for(size_t i = 0; i < layoutWindows_.size(); ++i)
    {
        if (layoutWindows_[i]->name() == name)
            return layoutWindows_[i];
        else
        {
            if (Content *c = layoutWindows_[i]->contentByName(name))
                return c;
        }
    }
    return 0;
}
