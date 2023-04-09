#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemAnimation>
#include <QPointF>
#include <QTimeLine>
#include <QTransform>
#include <math.h>
#include <vector>

#include "debugtools.h"
#include "lemonade.h"
#include "painter.h"

Painter::Painter(){
    DebugTools().strMsg("ERROR: canvas not initialized!");
}

Painter::Painter(QGraphicsScene *scene, int _total_animation_duration, int _frames, QBrush qbrush, QPen qpen){
    this->brush=qbrush;
    this->pen=qpen;
    this->canvas=scene;
    this->total_animation_duration=_total_animation_duration;
    this->frames=_frames;

    /*this->electron=new QGraphicsEllipseItem();
    std::cout<<electron->x()<<electron->y()<<std::endl;
    QTimeLine *timer = new QTimeLine(300);
    timer->setFrameRange(0, 100);*/
}

QGraphicsItem* Painter::drawLine(Line L){
    return this->drawLine(L, QColor("#000000"));
}
QGraphicsItem* Painter::drawLine(Line L, QColor color){
    return (QGraphicsItem*)(this->canvas->addLine(L.x0(), L.y0(), L.x1(), L.y1(), color));
}

QGraphicsItem* Painter::drawLine(QPointF P0, QPointF P1){
    return this->drawLine(P0, P1, QColor("#000000"));
}
QGraphicsItem* Painter::drawLine(QPointF P0, QPointF P1, QColor color){
    return (QGraphicsItem*)(this->canvas->addLine(P0.x(), P0.y(), P1.x(), P1.y(), color));
}

QGraphicsItemGroup* Painter::drawArrow(Line L0){
    return Painter::drawArrow(L0, QColor("#000000"));
}
QGraphicsItemGroup* Painter::drawArrow(Line L, QColor color){
    L.find_equationOfSelf();
    double* _k = &(L.equation_of_self.k);

    const int
        ARROW_HALF_WIDTH=4,
        ARROW_HEIGTH=16;
            /*_dx*_dy<0?
              -Physics_engine::PI/2 - atan(*_k):
               Physics_engine::PI/2 - atan(*_k);*/
    Point
        *p0=&L.p0,
        *p1=&L.p1;
    double
        aH_dx=
            ARROW_HEIGTH/
              sqrt ((*_k)*(*_k) + 1),
        aH_dy=aH_dx*(*_k),
        l_dx=L.dx(),
        l_dy=L.dy();

    const double
        move_dx=
            l_dx>0?
                l_dx-aH_dx:
                l_dx+aH_dx,
        move_dy=
            l_dx>0?
                -l_dy+aH_dy:
                -l_dy-aH_dy,
        angle=l_dx*l_dy<0?
                Physics_engine::PI/2 + atan(*_k):
                -Physics_engine::PI/2 + atan(*_k);
//    QPolygon arrowHead(
//        QVector{
//            QPoint(-ARROW_HALF_WIDTH, 0),
//            QPoint(0, -ARROW_HEIGTH),
//            QPoint( ARROW_HALF_WIDTH, 0),
//            QPoint(-ARROW_HALF_WIDTH, 0)
//        }
//    );
    Point arrowHead[] = {
        Point(-ARROW_HALF_WIDTH, 0).rotate(p0, angle).stat_move(move_dx, move_dy),
        Point(0, -ARROW_HEIGTH).rotate(p0, angle).stat_move(move_dx, move_dy),
        Point( ARROW_HALF_WIDTH, 0).rotate(p0, angle).stat_move(move_dx, move_dy)
    };

    QPolygon arrowHead_moved(
            QVector<QPoint>{
                arrowHead[0].toQPoint(),
                arrowHead[1].toQPoint(),
                arrowHead[2].toQPoint(),
                arrowHead[0].toQPoint()
            }
        );

    return canvas->createItemGroup(
                QList<QGraphicsItem*>{
                    this->drawLine(L),
                    this->drawPoly(&arrowHead_moved, QBrush(color))
                }
            );;
}

QGraphicsItem* Painter::drawPoly(Polygon* Poly, QBrush _brush){
    return (QGraphicsItem*)(this->canvas->addPolygon(Poly->to_qpoly(), this->pen, _brush));
}

QGraphicsItem* Painter::drawPoly(QPolygon* QPoly, QBrush _brush){
    return (QGraphicsItem*)(this->canvas->addPolygon(*QPoly, this->pen, _brush));
}

QGraphicsEllipseItem* Painter::drawCircle(Point* P, int radius, QBrush _brush){
    return this->canvas->addEllipse(P->x-radius, P->y-radius, radius*2, radius*2,this->pen, _brush);
}

QGraphicsItem* Painter::drawSurface(Polygon* surface){
    return this->drawPoly(surface, QBrush(QColor("#B9FFD1")));
}

QGraphicsEllipseItem* Painter::drawElectron(Point* electron){
    return this->drawCircle(electron, 5, QBrush(QColor("#FBFB3F")));
}

QGraphicsEllipseItem* Painter::drawVirt(Point* virt){
    return this->drawCircle(virt, 5, QBrush(QColor("#FFB9E7")));
}

QGraphicsItem* Painter::drawVector(Line _vector){
    QColor activeBrush_color = this->brush.color();
    this->brush.setColor(QColor("#000000"));
    QGraphicsItem* returned=(QGraphicsItem*)(this->drawLine(_vector));
    //draw triangle
    this->brush.setColor(activeBrush_color);
    return returned;
}

/*void Painter::setupElectronAnimation(Point *P0, Point *P1){
    this->animation_genuine = new QGraphicsItemAnimation;
    this->animation_genuine->setItem(this->drawElectron(P0));
    this->init_timer();
    this->animation_genuine->setTimeLine(this->animation_timer);
}*/

void Painter::setupAnimations(Point* ElP0, Point* VirP0){
    this->animation_virt    = new QGraphicsItemAnimation;
    this->animation_genuine = new QGraphicsItemAnimation;

    this->animation_virt   ->setItem(this->drawVirt(VirP0));
    this->animation_genuine->setItem(this->drawElectron(ElP0));

    this->init_timer();

    this->animation_virt   ->setTimeLine(this->animation_timer);
    this->animation_genuine->setTimeLine(this->animation_timer);
}

void Painter::stop_timer(){
    if(this->animation_timer){
        this->animation_timer->stop();
    }
}

void Painter::init_timer(){
    this->stop_timer();
    this->animation_timer=new QTimeLine(this->total_animation_duration);
    this->animation_timer->setFrameRange(0, this->frames);
}

/*

class Base {};
class Derived : public Base {};

Derived d;
Base b = d;

*/
