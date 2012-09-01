#include "programwidget.h"
#include <QGraphicsScene>
#include <Qt/QtOpenGL>


UI::ProgramWidget::ProgramWidget(QGraphicsScene *scene, QWidget *parent)
        : QGraphicsView(scene,parent)
{
    setViewport( new QGLWidget(QGLFormat(QGL::SampleBuffers)) );
}

void UI::ProgramWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
