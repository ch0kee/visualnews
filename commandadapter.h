#ifndef COMMANDADAPTER_H
#define COMMANDADAPTER_H

#include <QObject>
#include <QtNetwork>

class Scene;
class CommandAdapter : public QObject
{
  Q_OBJECT

public:
  CommandAdapter(Scene& scene);
  ~CommandAdapter();

public slots:
  void clientConnected();
private:
  QTcpServer* _tcpServer;
  QTcpSocket* _socket;
  Scene& _scene;
};

#endif // COMMANDADAPTER_H
