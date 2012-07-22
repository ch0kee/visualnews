#ifndef SCENEEVENTSHANDLER_H
#define SCENEEVENTSHANDLER_H

#include <vector>

class Scene;
namespace vnews
{
    class Thread;
    class SceneEventsHandler
    {
    public:
        SceneEventsHandler(Scene* s);
        void    addThread(Thread* thread);
        void    start();
        void    clear();
    private:
        Scene* _scene;
        std::vector<Thread*> _threads;
    };
}

#endif // SCENEEVENTSHANDLER_H
