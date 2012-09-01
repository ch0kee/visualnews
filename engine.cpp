#include "engine.h"
#include "session.h"
#include <QGraphicsScene>

#include "window.h"
#include "content.h"

#include "thread.h"

Engine::Engine()
    : _session(nullptr)
{
}

void Engine::setSession(const Session *session)
{
    _session = session;
}

void Engine::setScene(QGraphicsScene *scene)
{
    _scene = scene;
}

void Engine::fillScene()
{
    ///
    QString bgimagepath = _session->backgroundImagePath();
    _scene->setBackgroundBrush(QBrush(QImage(bgimagepath)));

    QRectF rect (QPointF(0.,0.),_session->resolution());
    _scene->setSceneRect(rect);
    ///

    ///
    const size_t countOfWindows = _session->countOfWindows();
    for(size_t i = 0; i < countOfWindows; ++i)
    {
        Window* w = new Window( _session->windowId(i) );
        w->setRect( _session->windowRect(i) );
        w->setZValue( _session->windowZLevel(i));
        addWindow(w);

        ///
        const size_t countOfContents = _session->countOfContents(i);
        for(size_t j = 0; j < countOfContents; ++j)
        {

            Content* c = Content::CreateContent(_session->contentId(i,j),
                                                _session->contentType(i,j),
                                                _session->contentUrl(i,j));
            Q_ASSERT( c );
            c->preload(w);
        }
        ///


    }
    ///

    ///
    const size_t countOfThreads = _session->countOfThreads();
    for(size_t i = 0; i < countOfThreads; ++i)
    {
        Thread* t = new Thread/*( _scene )*/;
        addThread(t);
        ///
        size_t countOfEvents = _session->countOfEvents(i);
        for(size_t j = 0; j < countOfEvents; ++j)
        {
            QString targetName = _session->eventAttribute("Target",i,j);
            if (targetName.isNull())
            {
                Event* e = t->createEvent(_session->eventName(i,j),
                                          _session->firstEventAttribute(i,j));
                t->addEvent(e);
            }
            else
            {
                SceneObject* o = sceneObjectByName(targetName);
                Event* e = o->createEvent(_session->eventName(i,j));
                t->addEvent(e);
            }
        }

#if 0
      Thread * t = _scene->threads().last();
      Q_ASSERT( t != 0 );
      QString targetName = attributes.value("Target");

      if (targetName.isNull() || targetName.isEmpty())
      {
          Event* e = t->createEvent(attributes);
          t->addEvent(e);
      }
      else
      {
          SceneObject* o = _scene->layout().sceneObjectByName(targetName);
          Event* e = o->createEvent(attributes);
          t->addEvent(e);
      }
#endif
        ///
    }
    ///

    ///
    ///


}

void Engine::startAnimation()
{
    for(uint i = 0; i < _threads.size(); ++i)
    {
        _threads[i]->start();
    }
}

void Engine::addWindow(Window* window)
{
    _windows.push_back(window);
    _scene->addItem( window->graphicsItem() );
    window->graphicsItem()->setVisible(true);
}

void Engine::addThread(Thread* thread)
{
    Q_ASSERT(thread != 0);
    _threads.push_back( thread );
}

Window* Engine::windowByName(const QString& name)
{
    for(size_t i = 0; i < _windows.size(); ++i)
    {
        if (_windows[i]->name() == name)
            return _windows[i];
    }
    return 0;
}

Content* Engine::contentByName(const QString& name)
{
    for(size_t i = 0; i < _windows.size(); ++i)
    {
        Content *c = _windows[i]->contentByName(name);
        if (c)
            return c;
    }
    return 0;
}


SceneObject* Engine::sceneObjectByName(const QString &name)
{
    for(size_t i = 0; i < _windows.size(); ++i)
    {
        if (_windows[i]->name() == name)
            return _windows[i];
        else
        {
            if (Content *c = _windows[i]->contentByName(name))
                return c;
        }
    }
    return 0;
}
