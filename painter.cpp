#include "debugtools.h"
#include "painter.h"
#include <QGraphicsScene>
#include <vector>

Painter::Painter(){
    DebugTools().strMsg("ERROR: canvas not initialized!");
}

Painter::Painter(QGraphicsScene *scene, QBrush qbrush, QPen qpen){
    this->brush=qbrush;
    this->pen=qpen;
    this->canvas=scene;
}

QGraphicsItem* Painter::drawLine(Line L){
    return (QGraphicsItem*)(this->canvas->addLine(L.x0(), L.y0(), L.x1(), L.y1()));
}

QGraphicsItem* Painter::drawPoly(Polygon Poly){
    return (QGraphicsItem*)(this->canvas->addPolygon(Poly.to_qpoly(), this->pen, this->brush));
}

QGraphicsItem* Painter::drawCircle(Point P, int radius){
    return (QGraphicsItem*)(this->canvas->addEllipse(P.x-radius, P.y-radius, radius*2, radius*2,this->pen, this->brush));
}


/*

class Base {};
class Derived : public Base {};

Derived d;
Base b = d;

*/
