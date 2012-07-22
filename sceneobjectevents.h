#ifndef SCENEOBJECTEVENTS_H
#define SCENEOBJECTEVENTS_H

#include "event.h"
#include <QGraphicsItemAnimation>

class QTimeLine;
namespace vnews
{
    class IHasGraphicsItem;

    namespace Events
    {
        class ShowSceneObject : public Event
        {
            Q_OBJECT
        public:
            ShowSceneObject(IHasGraphicsItem* sceneObject);
            ~ShowSceneObject();
        public Q_SLOTS:
            void start();
        private:
            IHasGraphicsItem* sceneObject_;
        };

        class HideSceneObject : public Event
        {
            Q_OBJECT
        public:
            HideSceneObject(IHasGraphicsItem* sceneObject);
            ~HideSceneObject();
        public Q_SLOTS:
            void start();
        private:
            IHasGraphicsItem* sceneObject_;
        };

        class FadeInSceneObject : public Event
        {
            Q_OBJECT
        public:
            FadeInSceneObject(IHasGraphicsItem* sceneObject);
            ~FadeInSceneObject();
        public Q_SLOTS:
            void start();
        private:
            IHasGraphicsItem* _sceneObject;
            QTimeLine* _timeLine;

            struct FadeInAnimation : public QGraphicsItemAnimation
            {
                FadeInAnimation(QObject* parent);
                void beforeAnimationStep( qreal step );
            }* _animation;
        };

        class FadeOutSceneObject : public Event
        {
            Q_OBJECT
        public:
            FadeOutSceneObject(IHasGraphicsItem* sceneObject);
            ~FadeOutSceneObject();
        public Q_SLOTS:
            void start();
        private Q_SLOTS:
            void beforeFinished();
        private:
            IHasGraphicsItem* _sceneObject;
            QTimeLine* _timeLine;

            struct FadeOutAnimation : public QGraphicsItemAnimation
            {
                FadeOutAnimation(QObject* parent);
                void beforeAnimationStep( qreal step );
            }* _animation;
        };

        class ScrollSceneObject : public Event
        {
            Q_OBJECT
        public:
            ScrollSceneObject(IHasGraphicsItem* sceneObject);
            ~ScrollSceneObject();
        public Q_SLOTS:
            void start();
        private:
            IHasGraphicsItem* _sceneObject;
            QGraphicsItemAnimation* _animation;
            QTimeLine* _timeLine;
        };

    }
}
#endif // SCENEOBJECTEVENTS_H
