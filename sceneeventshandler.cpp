#include "sceneeventshandler.h"
#include "scene.h"
#include "thread.h"

using namespace vnews;

SceneEventsHandler::SceneEventsHandler(Scene* s)
    : _scene(s)
{
}


void SceneEventsHandler::addThread(Thread* thread)
{
    Q_ASSERT(thread != 0);
    _threads.push_back( thread );
}

void SceneEventsHandler::start()
{
    for(uint i = 0; i < _threads.size(); ++i)
    {
        _threads[i]->start();
    }
}

void SceneEventsHandler::clear()
{
//le kell állítani az összes szálat
    Q_FOREACH(Thread* t, _threads)
    {
        delete t;
    }
    _threads.clear();
}
