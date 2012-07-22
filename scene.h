#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "scenelayouthandler.h"
#include "sceneeventshandler.h"
#include <QString>
#include "commandadapter.h"

#include <vector>
class QTimeLine;
class Tokens;

class Thread;
class Scene : public QGraphicsScene
{
  Q_OBJECT
public:
  Scene();

  void fillScene(const QString& filename);

  void keyPressEvent ( QKeyEvent * keyEvent );

  vnews::SceneEventsHandler& threads() { return _threads; }
  vnews::SceneLayoutHandler& layout() { return _layout; }

  QGraphicsView* getMainView() const { return this->views().first(); }

  void start();
  void stop();

  void  setSession(const QString& sessionFilename);
signals:
  void started();
private:
  vnews::SceneEventsHandler _threads;
  vnews::SceneLayoutHandler _layout;

  QString _lastFilename;
  CommandAdapter _cmdAdapter;

};

#endif // SCENE_H
