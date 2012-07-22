#include "scenelayouthandler.h"
#include "window.h"
#include "scene.h"

vnews::SceneLayoutHandler::SceneLayoutHandler(Scene* s)
    : _scene(s)
{
}

void    vnews::SceneLayoutHandler::clear()
{
    Q_FOREACH(Window* w, layoutWindows_)
    {
        delete w;
    }
    layoutWindows_.clear();
}

vnews::Window* vnews::SceneLayoutHandler::windowByName(const QString& name)
{
    for(size_t i = 0; i < layoutWindows_.size(); ++i)
    {
        if (layoutWindows_[i]->name() == name)
            return layoutWindows_[i];
    }
    return 0;
}

void vnews::SceneLayoutHandler::addWindow(Window* window)
{
    layoutWindows_.push_back(window);
    _scene->addItem( window->graphicsItem() );
    window->graphicsItem()->setVisible(true);
}
