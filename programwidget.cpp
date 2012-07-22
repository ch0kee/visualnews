#include "programwidget.h"
#include <QGraphicsScene>
#include <Qt/QtOpenGL>


UI::ProgramWidget::ProgramWidget(QGraphicsScene* scene)
        : QGraphicsView(scene, 0)
{
    setViewport( new QGLWidget(QGLFormat(QGL::SampleBuffers)) );
}

void UI::ProgramWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
