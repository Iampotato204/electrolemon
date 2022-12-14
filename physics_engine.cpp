#include "debugtools.h"
#include "physics_engine.h"
#include "lemonade.h"
#include <math.h>
using std::max;
using std::min;
// class Physics_engine //

Physics_engine::Physics_engine(){

}

void Physics_engine::change_particle_position(double dx, double dy){

}

void Physics_engine::recalculate(double time){

}

Line Physics_engine::rotateVector(Point p0, Point p1, int eulerAngle){
    double radian = eulerAngle*PI/180;
    int x0=p0.x,
        y0=p0.y,
        x1=p1.x-x0,
        y1=p1.y-y0;
    return Line(p0,Point(
                    x0 + x1*cos(radian)-y1*sin(radian),
                    y0 + x1*sin(radian)+y1*cos(radian)));
}

Line Physics_engine::scaleVector(Point p0, Point p1, double multiplier){
    int x0=p0.x,
        y0=p0.y,
        x1=p1.x-x0,
        y1=p1.y-y0;
    return Line(p0,Point(
                    x0 + x1*multiplier,
                    y0 + y1*multiplier));
}

bool Physics_engine::findProjection(Point, Line){
    return true;
}

bool Physics_engine::findKollision(Line moving, Line surface_line){
    Point p1=moving.p0;
    Point p2=moving.p1;
    Point p3=surface_line.p0;
    Point p4=surface_line.p1;
    // lines are: p1p2, p3p4

    // start point of each line should be at left
    if (p2.x<p1.x) {
        Point tmp=p1;
        p1=p2;
        p2=tmp;
    }
    if (p4.x<p3.x) {
        Point tmp=p3;
        p3=p4;
        p4=tmp;
    }

    int x[]={p1.x, p2.x, p3.x, p4.x};
    int y[]={p1.y, p2.y, p3.y, p4.y};

    // f1(x)=k1*x+b1=y
    // f2(x)=k2*x+b2=y
    double Xres, Yres, b1, b2, k1, k2;

    // check if they possibly can intersect
    if (x[1]<x[2]) {return false;}
    // if both are vertical
    if((x[0]-x[1] == 0) && (x[2]-x[3] == 0)) {return false;}

    // if first line is vertical
    if (x[0]-x[1] == 0) {
        Xres= x[0];
        k2= (y[2]-y[3]) / (x[2]-x[3]);
        b2= y[2]-k2 * x[2];
        Yres= k2*Xres+b2;
        if ((x[2]<=Xres && x[3]>=Xres)  &&  (min(y[0],y[1])<=Yres && max(y[0],y[1])>=Yres)) {
            this->kollision=Point(Xres, Yres);
            return true;
        }
        return false;
    }

    // if second line is vertical
    if (x[2]-x[3] == 0) {
        Xres= x[2];
        k1= (y[0]-y[1]) / (x[0]-x[1]);
        b1= y[0]-k1*x[0];
        Yres= k1*Xres+b1;
        if ((x[0]<=Xres && x[1]>=Xres)  &&  (min(y[2],y[3])<=Yres && max(y[2],y[3])>=Yres)) {
            this->kollision=Point(Xres, Yres);
            return true;
        }
        return false;
    }

    k1= (y[0]-y[1]) / (x[0]-x[1]);
    k2= (y[2]-y[3]) / (x[2]-x[3]);
    if (k1==k2) {return false;}

    b1= y[0]-k1*x[0];
    b2= y[2]-k2*x[2];

    Xres=(b2-b1) / (k1-k2);
    /*if ((Xres<max(x[0], x[2])) || (Xres > min( x[1], x[3]))) {
        return false;
    }*/
    Yres=k1*Xres+b1;
    this->kollision=Point(Xres, Yres);
    return true;
}


/*
std::ostream & operator<<(std::ostream & out, Point & P){
    out<<"("<<P.x<<";"<<P.y<<")";
    return out;
}

std::ostream & operator<<(std::ostream & out, Line & L){
    out<<L.p0<<"_"<<L.p1;
    return out;
}

std::ostream & operator<<(std::ostream & out, Polygon & Poly){
    for(Line l: Poly.polygon){
        out<<"<"<<l<<">  ";
    }
    out<<std::endl;
}*/

std::ostream & operator<<(std::ostream & out, Point & P){
    return out<<"("<<P.x<<";"<<P.y<<")";}

std::ostream & operator<<(std::ostream & out, Line & L){
    return out<<L.p0<<"_"<<L.p1;}

std::ostream & operator<<(std::ostream & out, Polygon & Poly){
    for(Line l: Poly.polygon) out<<"<"<<l<<">  ";
    return out<<std::endl;
}

//             //
// class Point //
//             //


Point::Point(){
    this->x=0;
    this->y=0;
}

Point::Point(int _x, int _y){
    this->x=_x;
    this->y=_y;
}


//            //
// class Line //
//            //


Line::Line(){
    this->p0=Point();
    this->p1=Point();
}

Line::Line(Point _p0, Point _p1){
    this->p0=_p0;
    this->p1=_p1;
}

Line::Line(int _x0, int _y0, int _x1, int _y1){
    this->p0=Point(_x0,_y0);
    this->p1=Point(_x1,_y1);
}

int Line::x0(){
    return this->p0.x;
}

int Line::y0(){
    return this->p0.y;
}

int Line::x1(){
    return this->p1.x;
}

int Line::y1(){
    return this->p1.y;
}

QLineF Line::to_qline(){
    return QLineF(QPointF(x0(), y0()), QPointF(x1(), y1()));
}

//               //
// class Polygon //
//               //

Polygon::Polygon(){
    this->polygon={};
}

Polygon::Polygon(std::vector<Line> poly){
    this->polygon=poly;
}

QPolygonF Polygon::to_qpoly(){
    QVector<QPointF> qpoints;
    for(Line l: this->polygon){
        qpoints.push_back(QPointF(l.x0(),l.y0()));
    }
    return QPolygonF(qpoints);
}
