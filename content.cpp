#include <QFile>
#include <QPixmap>
#include <QByteArray>
#include <QPainter>
#include <QTextStream>
#include <QThread>
#include "content.h"
#include <iostream>
#include <QXmlAttributes>
#include <QGraphicsScene>
#include "sceneobjectevents.h"

#include <QDebug>
#include <QDir>
#include "scene.h"

#include <QFutureWatcher>
#include <QApplication>
#include <QEventLoop>
using namespace std;



Content* Content::CreateContent(const QString& id, const QString& type, const QString& url)
{
    Content* c = 0;
    //@ Content Type
    if (type == "html")
    {
        c = new HtmlContent();
    }
    else if (type == "image")
    {
        c = new ImageContent();
    }
    else if (type == "text")
    {
        c = new TextContent();
    }
    Q_ASSERT( c != 0 );

    c->_name = id;
    c->_url = url;

    return c;
}

Content::Content()
    : graphicsItem_(0)
{}

Content::~Content()
{
    graphicsItem_->scene()->removeItem(graphicsItem_);
    delete graphicsItem_;
}


void Content::preload(Window* window)
{
    Q_ASSERT(graphicsItem_ == 0);
    graphicsItem_ = createGraphicsItem(window->childrenBoundingRect());
    graphicsItem_->setVisible(false);
    Q_ASSERT(graphicsItem_ != 0);

    window->addContent(this);
}

HtmlContent::HtmlContent()
    : _webPage(nullptr)
{
}

QGraphicsItem* HtmlContent::createGraphicsItem(const QRectF& rect)
{
    QFile file(_url);
    if (!file.open(QIODevice::ReadOnly))
        throw 0;

    QPixmap pm( rect.size().toSize() );
    _webPage = new QWebPage();
    _webPage->setViewportSize( pm.size());
    _webPage->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    _webPage->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);


    {
        _webPage->mainFrame()->load(QUrl(_url));
        qDebug() << "Executing load [" << _url << "]...";
        QApplication::processEvents( QEventLoop::AllEvents, 80);
        qDebug() << "DONE Executed.";
    }



     QPainter p;
     p.begin(&pm);
     qDebug() << "Start rendering " << _url;
     _webPage->mainFrame()->render(&p);
     qDebug() << "Rendered done " << _url;
     p.end();
    delete _webPage;

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
    item->setPixmap(pm);
    return item;
}


QGraphicsItem* ImageContent::createGraphicsItem(const QRectF& rect)
{
    QPixmap pm( rect.size().toSize() );
    QPainter p;
    p.begin(&pm);
    p.drawImage( QRect( QPoint(0,0), pm.size() ), QImage(_url) );
    p.end();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
    item->setPixmap( pm );
    return item;
}


QGraphicsItem* TextContent::createGraphicsItem(const QRectF& rect)
{

    QFile   file(_url);
    if(!file.open(QIODevice::ReadOnly))
        throw 0;

    int rectHeight = rect.height();

    QTextStream in(&file);
    QString text (in.readAll());

    QGraphicsSimpleTextItem* item = new QGraphicsSimpleTextItem();
    // measuring text
    QFont newFont( item->font() );
    newFont.setStyleStrategy( QFont::OpenGLCompatible );
    int textSize = 0;
    int textHeightInPixels = 1;
    while(textHeightInPixels < rectHeight)
    {
        ++textSize;
        newFont.setPointSize(textSize);
        QFontMetrics fm(newFont);
        fm.width(text);
        textHeightInPixels = fm.height();
    }

    newFont.setPointSize( textSize-1 );
    item->setFont( newFont );
    item->setText( text );

    return item;
}
