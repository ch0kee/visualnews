
#include <QtNetwork>
#include "commandadapter.h"
#include <iostream>
#include "exceptions.h"
#include <QDataStream>
#include <QDebug>
#include <QPainter>
#include "scene.h"

#include "JlCompress.h"
#include <fstream>

CommandAdapter::CommandAdapter(Scene& scene)
    : _tcpServer(0), _scene(scene)
{
  _tcpServer = new QTcpServer(this);
  QObject::connect(_tcpServer, SIGNAL(newConnection()),
                   this, SLOT(clientConnected()));

  QFile in("visualnews.config");
  in.open(QFile::ReadOnly);

  QString ip, port;

  ip = in.readLine();
  port = in.readLine();

  in.close();

  bool ok = _tcpServer->listen(QHostAddress(ip), port.toInt());
  if (!ok)
    throw Exception<EET_NETWORKERROR>("can't start tcp server");
  else
  {
      qDebug() << "TCP server started.";
  }
}

CommandAdapter::~CommandAdapter()
{


}

class ClientConnection
{
public:
    ClientConnection(QTcpSocket* socket)
        : _socket(socket)
    {
        qDebug() << "Incoming connection attempt.";
    }

    ~ClientConnection()
    {
        //delete _socket;
        qDebug() << "Connection attempt closed.";
    }

public:


    bool receiveFile(const QString& fileDest)
    {
        qint64 fileSize;
        QByteArray data;
        if (_socket->waitForReadyRead())
        {
            //////
              QByteArray in = _socket->read(8);
              QDataStream(in) >> fileSize;
              qDebug() << "Incoming file size " << fileSize;

              for(qint64 filePtr = 0; filePtr < fileSize; filePtr += in.size())
              {
                _socket->waitForReadyRead();
                in = _socket->read(256);
                qDebug() << "SegmentSize=" << in.size();
                data.append(in);
              }
              qDebug() << "Success. Size=" << data.size();


            //////
            if (data.size() > 0)
            {
                QFile* f = new QFile(fileDest);
                if (!f->open(QIODevice::WriteOnly|QIODevice::Truncate))
                {
                    qDebug() << "!! Can't open file [" << fileDest << "]";
                    delete f;
                    return false;
                }

                qint64 bytesWrote = f->write(data);
                f->flush();
                if (bytesWrote != data.length())
                {
                    qDebug() << "!! Can't write buffer(" << data.size() << ") into file(" << bytesWrote << ").";
                    f->remove();
                    delete f;
                    return false;
                }
                qDebug() << "File saved.";
                f->close();
                delete f;
                return true;

            }
            else
            {
                qDebug() << "!! Zero sized file received.";
                return false;
            }
        }
        qDebug() << "!! No file received.";
        return false;

    }

private:
    void sendInt64(qint64 i64)
    {
        QByteArray buffer;
        QDataStream out(&buffer, QIODevice::WriteOnly);
        out << i64;
        qDebug() << "Sending Int64... [" << i64 << "]";
        qint64 bytesWrote = _socket->write(buffer,8);
        qDebug() << "Sent bytes : " << bytesWrote;
    }

    qint64 receiveInt64()
    {
        qint64 i64(-1);
        if (_socket->waitForReadyRead(5000))
        {
            QByteArray in = _socket->read(8);
            QDataStream(in) >> i64;
            qDebug() << "Data arrived. [" << i64 << "]";
        }
        else
        {
            qDebug() << "!! Expected data didn't arrive.";

        }
        return i64;
    }


private:

    QTcpSocket* _socket;

};

const int Timeout = 5 * 1000;
void CommandAdapter::clientConnected()
{
    qDebug() << "Client connected.";
    _socket = _tcpServer->nextPendingConnection();
    ClientConnection cc(_socket);
    bool responded = _socket->waitForReadyRead();
    if (responded)
    {
        //uj tartalom letöltése
        QString pkgFilename = QDir::temp().absoluteFilePath("vnsession.vnp");
        bool recvd = cc.receiveFile(pkgFilename);
        if (recvd)
        {
            qDebug() << "Session file received. " << pkgFilename;
            QDir targetDir = QDir::current();
            qDebug() << "Extracting...";

            QStringList xtrd = JlCompress::extractDir(pkgFilename, targetDir.absolutePath());
            for(int i = 0; i < xtrd.size(); ++i)
            {
                qDebug() << ".." << xtrd[i];
            }
            qDebug() << "Extracted.";
            xtrd = xtrd.filter(".vnsession");
            if (!xtrd.empty())
            {
                qDebug() << "Starting new session..." << xtrd.first();
                _scene.setSession(xtrd.first());
                qDebug() << "DONE";

            }
            else
            {
                qDebug() << "No session file received.";
            }
        }
        else
        {
            qDebug() << "!! Receive failed.";
            return;
        }
    }
    else
    {
        qCritical() << "Socket did not respond";
    }
    _socket->close();
    _socket->deleteLater();
}
