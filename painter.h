#ifndef PAINTER_H
#define PAINTER_H

#include <QColor>
#include <QObject>
#include <QGraphicsScene>
#include "physics_engine.h"

class Painter : public QObject
{
    Q_OBJECT
public:

    QBrush brush;
    QPen pen;
    QGraphicsScene *canvas;
    std::vector<Polygon> metasurface;

    Painter();
    Painter(QGraphicsScene *, QBrush = QBrush(QColor("#b9ffd1")), QPen=QPen(Qt::black,2));

    QGraphicsItem* drawLine(Line);
    QGraphicsItem* drawPoly(Polygon);
    QGraphicsItem* drawCircle(Point, int);

};

#endif // PAINTER_H
