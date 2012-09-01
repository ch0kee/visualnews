#ifndef SCENELAYOUTHANDLER_H
#define SCENELAYOUTHANDLER_H
#include <vector>
#include <QString>

class Scene;
    class SceneObject;
    class Window;
    class Content;
    class SceneLayoutHandler
    {
    public:
        SceneLayoutHandler(Scene* s);

        //void addWindow(Window* window);

        SceneObject* sceneObjectByName(const QString& name);

        Window* windowByName(const QString& name);
        Content* contentByName(const QString& name);
        void    clear();

        Window* lastWindow() { return layoutWindows_.back(); }

    private:
        Scene*  _scene;
        std::vector<Window*> layoutWindows_;
    };
#endif // SCENELAYOUTHANDLER_H
