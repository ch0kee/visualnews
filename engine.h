#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

class QString;
class Window;
class Thread;
class Session;
class QGraphicsScene;
class SceneObject;
class Content;

class Engine
{
public:
    Engine();
    void    setSession(const Session* session);
    void    setScene(QGraphicsScene* scene);

    void    fillScene();

    void    startAnimation();
private:
    void    addThread(Thread *thread);
    void    addWindow(Window* window);
    SceneObject*    sceneObjectByName(const QString& name);

    Window*         windowByName(const QString& name);
    Content*        contentByName(const QString& name);

    QGraphicsScene* _scene;
    const Session* _session;

    std::vector<Window*> _windows;
    std::vector<Thread*> _threads;
};

#endif // ENGINE_H
