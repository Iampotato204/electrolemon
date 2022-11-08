#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QGraphicsScene>
#include "physics_engine.h"

class Painter : public QObject
{
    Q_OBJECT
public:
    QBrush brush;
    QGraphicsScene *canvas;
    std::vector<Polygon> metasurface;

    Painter();
    Painter(QGraphicsScene *, std::vector<Polygon>, QBrush = QBrush(Qt::white));

    QGraphicsItem* drawLine(Line);
    QGraphicsItem* drawPoly(Polygon);
};

#endif // PAINTER_H
