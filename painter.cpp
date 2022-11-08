#include "debugtools.h"
#include "painter.h"
#include <QGraphicsScene>
#include <vector>

Painter::Painter(){
    DebugTools().strMsg("ERROR: canvas not initialized!");
}

Painter::Painter(QGraphicsScene *scene, std::vector<Polygon> surface, QBrush qbrush){
    this->brush=qbrush;
    this->canvas=scene;
    this->metasurface=surface;
}

QGraphicsItem* Painter::drawLine(Line L){
    //QGraphicsItem *res=(QGraphicsItem*)(this->canvas->addLine(L.x0(), L.y0(), L.x1(), L.y1()));
    std::cout<<"Added line is: "<<L<<"  "<</*res<<*/std::endl;
    return (QGraphicsItem*)(this->canvas->addLine(L.x0(), L.y0(), L.x1(), L.y1()));
}

QGraphicsItem* Painter::drawPoly(Polygon Poly){
    std::cout<<"Added polygon is: "<<Poly<<"  "<</*res<<*/std::endl;
    return (QGraphicsItem*)(this->canvas->addPolygon(Poly.to_qpoly()));
}


/*

class Base {};
class Derived : public Base {};

Derived d;
Base b = d;

*/
