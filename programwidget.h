#ifndef PROGRAMWIDGET_H
#define PROGRAMWIDGET_H

#include <QGraphicsView>

namespace UI
{
    class ProgramWidget : public QGraphicsView
    {
        Q_OBJECT
    public:
        ProgramWidget(QGraphicsScene* scene , QWidget* parent=0);
    protected:
        void resizeEvent(QResizeEvent *event);
    };
}


#endif // PROGRAMWIDGET_H
