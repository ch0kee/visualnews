#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "scenelayouthandler.h"
#include "sceneeventshandler.h"
#include <QString>

#include <vector>
class QTimeLine;
class Tokens;
class QGraphicsView;
class Thread;

class ViewKeyboardFilter
        : public QObject
{
    Q_OBJECT
public:
    ViewKeyboardFilter(QGraphicsView* view);

    bool eventFilter(QObject *obj, QEvent *ev);
private:
    QGraphicsView* _view;

};

class Scene : public QGraphicsScene
{
  Q_OBJECT
public:
  Scene();

  void setView( QGraphicsView* view);

  void fillScene(const QString& filename);

  //void keyPressEvent ( QKeyEvent * keyEvent );

  SceneEventsHandler& threads() { return _threads; }
  SceneLayoutHandler& layout() { return _layout; }

  QGraphicsView* getMainView() const { return this->views().first(); }

  void start();
  void stop();


  void  setSession(const QString& sessionFilename);
signals:
  void started();
private:
  SceneEventsHandler _threads;
  SceneLayoutHandler _layout;

  QString _lastFilename;

};

#endif // SCENE_H
