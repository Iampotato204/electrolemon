#ifndef PAINTER_H
#define PAINTER_H
//painter.h
#include <QColor>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItemAnimation>
#include <QPoint>

#include "physics_engine.h"

class Painter : public QObject
{
    Q_OBJECT
public:
    Painter();
    Painter(QGraphicsScene *, int frame_duration, int frames, QBrush = QBrush(QColor("#b9ffd1")), QPen=QPen(Qt::black,2));

    QGraphicsItem* drawSurface(Polygon* Poly);
    QGraphicsEllipseItem* drawElectron(Point* P);
    QGraphicsEllipseItem* drawVirt(Point* P);
    QGraphicsItem* drawVector(Line);

    QGraphicsItem* drawLine(Line);
    QGraphicsItem* drawLine(Line, QColor);
    QGraphicsItem* drawLine(QPointF, QPointF);
    QGraphicsItem* drawLine(QPointF, QPointF, QColor);
    QGraphicsItemGroup* drawArrow(Line, QColor);
    QGraphicsItemGroup* drawArrow(Line);

    QTimeLine *animation_timer=nullptr;
    QGraphicsItemAnimation *animation_genuine=nullptr,
                           *animation_virt=nullptr;

    //void setupElectronAnimation(Point* P0, Point* P1);
    //void setupVirtAnimation(Point* P0, Point* P1);
    void setupAnimations(Point* ElP0, Point* VirP0);

    //void setupVectorAnimation(Line);
    void init_timer();
    void stop_timer();

private:
    QBrush brush;
    QPen pen;
    QGraphicsScene *canvas;

//    QGraphicsItem* metasurface=nullptr;
//    QGraphicsItem* electron=nullptr;
//    QGraphicsItem* movementVector=nullptr;

    QGraphicsItem* drawPoly(Polygon*, QBrush);
    QGraphicsItem* drawPoly(QPolygon*, QBrush);
    QGraphicsEllipseItem* drawCircle(Point*, int, QBrush);

    int total_animation_duration;
    int frames;
};

#endif // PAINTER_H
