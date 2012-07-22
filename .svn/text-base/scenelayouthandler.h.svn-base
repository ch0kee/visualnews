#ifndef SCENELAYOUTHANDLER_H
#define SCENELAYOUTHANDLER_H
#include <vector>
#include <QString>

class Scene;
namespace vnews
{
    class Window;
    class SceneLayoutHandler
    {
    public:
        SceneLayoutHandler(Scene* s);

        void addWindow(Window* window);

        Window* windowByName(const QString& name);
        void    clear();

    private:
        Scene*  _scene;
        std::vector<Window*> layoutWindows_;
    };
}

#endif // SCENELAYOUTHANDLER_H
