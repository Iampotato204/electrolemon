#include <QGraphicsScene>
#include <vector>

#include "debugtools.h"
#include "lemonade.h"
#include "painter.h"

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

void Painter::drawSurface(){
    QColor activeBrush_color = this->brush.color();
    this->brush.setColor(QColor("#b9ffd1"));
    this->drawPoly(Physics_engine.metasurface_genuine);
    this->brush.setColor(activeBrush_color);
}
void Painter::drawElectron(){
    QColor activeBrush_color = this->brush.color();
    this->brush.setColor(QColor("#fbfb3f"));
    this->drawCircle(Physics_engine.electron_genuine, 5);
    this->brush.setColor(activeBrush_color);
}
void Painter::drawVector(Line _vector){
    QColor activeBrush_color = this->brush.color();
    this->brush.setColor(QColor("#000000"));
    this->drawLine(_vector);
    //draw triangle
    this->brush.setColor(activeBrush_color);
}


/*

class Base {};
class Derived : public Base {};

Derived d;
Base b = d;

*/
