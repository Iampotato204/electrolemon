#include <iomanip>
#include "debugtools.h"
#include "physics_engine.h"
#include "lemonade.h"
#include <math.h>
#include <typeinfo>
#include <QPointF>
using std::max;
using std::min;
// class Physics_engine //

Physics_engine::Physics_engine(){

}

void Physics_engine::calculate_acceleration(){
    this->acceleration_mantissa=get_acceleration_mantissa();
    this->acceleration_exponent=get_acceleration_exponent();
    this->acceleration=this->acceleration_mantissa*pow(10,this->acceleration_exponent);
}

double Physics_engine::get_acceleration_mantissa(){
    return
        4 * k_mantissa * p_q_mantissa*p_q_mantissa /
        (p_m_mantissa * Line(this->electron_genuine,this->base_of_perpendicular).square_of_length());
}

int Physics_engine::get_acceleration_exponent(){
    return k_exponent + p_q_exponent*2 - p_m_exponent;// + distance_scale_exponent;
}

double Physics_engine::movementVectorStart_length(){
    return sqrt(pow(v0_x,2)+
                pow(v0_y,2));
}

int Physics_engine::mod_i(int a){
    return a>=0?a:-a;
}

double Physics_engine::mod_d(double a){
    return a>=0?a:-a;
}

double Physics_engine::radian(double _ang){
    return _ang*PI/180;
}

double Physics_engine::angle(double _rad){
    return _rad*180/PI;
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

void Physics_engine::find_base_of_perpendicular(Line l){
    l.find_equations(this->electron_genuine);
    double _x0=(l.equation_of_perpendicular.b - l.equation_of_self.b)/
                (l.equation_of_self.k - l.equation_of_perpendicular.k);
    double _y0=l.equation_of_self.k*_x0+l.equation_of_self.b;
//    std::cout<<"-k0= "<<std::setprecision(5)<<-l.equation_of_self.k<<std::endl;
//    std::cout<<"x0= "<<std::setprecision(5)<<_x0<<std::endl;
//    std::cout<<"b0= "<<std::setprecision(5)<<l.equation_of_self.b<<std::endl;

    this->base_of_perpendicular=Point(_x0, -_y0);
}

/*
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
//    if ((Xres<max(x[0], x[2])) || (Xres > min( x[1], x[3]))) {
//        return false;
//    }
//    Yres=k1*Xres+b1;
//    this->kollision=Point(Xres, Yres);
//    return true;
}
*/


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


//             //
// class Point //
//             //


Point::Point(){
    this->x=0;
    this->y=0;
}

Point::Point(double _x, double _y){
    this->x=_x;
    this->y=_y;
}

Point Point::rotate(Point* center, double rad){
    double
        dx=this->x-center->x,
        dy=-this->y+center->y;
    return Point( center->x + dx*cos(rad)-dy*sin(rad),
                  center->y - (dx*sin(rad)+dy*cos(rad)));
}

Point Point::rotateAround00(double rad){
    double
        s=sin(rad),
        c=cos(rad);
    return Point(this->x*c+this->y*s,
                 this->y*c-this->x*s);
}

Point* Point::move(double dx, double dy){
    this->x+=dx;
    this->y+=dy;
    return this;
}

Point Point::stat_move(double dx, double dy){
    this->x+=dx;
    this->y+=dy;
    return *this;
}

QPointF Point::toQPointF(){
    return QPointF(this->x, this->y);
}

QPoint Point::toQPoint(){
    return QPoint(this->x, this->y);
}


//                     //
// class Line_equation //
//                     //

Line_equation::Line_equation(){
    this->k=1;
    this->b=0;
}

Line_equation::Line_equation(double _k, double _b){
    this->k=_k;
    this->b=_b;
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

Line::Line(double _x0, double _y0, double _x1, double _y1){
    this->p0=Point((int)_x0,(int)_y0);
    this->p1=Point((int)_x1,(int)_y1);
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

int Line::dx(){
    return this->x1()-this->x0();
}

int Line::dy(){
    return this->y0()-this->y1();
}

//left for backwards compatibility
void Line::find_equations(Point _electron){
    this->find_equationOfSelf();
    this->find_equationOfPerpendicular(_electron);
}

void Line::find_equationOfSelf(){
    double k1=((double)(y0()-y1())) / ((double)(x1()-x0())); //-(y1-y0)/(x1-x0)
    double b1=(double)-y0() - ((double)x0())*k1;
    this->equation_of_self=Line_equation(k1,b1);
    std::cout<<"k1= "<<std::setprecision(5)<<k1<<std::endl<<
               "b1= "<<std::setprecision(5)<<b1<<std::endl;
}

void Line::find_equationOfPerpendicular(Point _electron){
    double k1=((double)(y0()-y1())) / ((double)(x1()-x0())); //-(y1-y0)/(x1-x0)
    double k2=-1.0/k1;
    double b2=(double)-_electron.y - ((double)_electron.x)*k2;
    this->equation_of_perpendicular=Line_equation(k2,b2);
    std::cout<<"k2= "<<std::setprecision(5)<<k2<<std::endl<<
               "b2= "<<std::setprecision(5)<<b2<<std::endl;
}

QLineF Line::to_qline(){
    return QLineF(QPointF(x0(), y0()), QPointF(x1(), y1()));
}

double Line::length(){
    return sqrt(pow(x1()-x0(),2)+pow(y1()-y0(),2));
}

double Line::square_of_length(){
    return pow(x1()-x0(),2)+pow(y1()-y0(),2);
}

//               //
// class Polygon //
//               //

Polygon::Polygon(){
    this->polygon={};
    /*Line(-100, -100, 100, -100),
    Line(100, -100, 100, 100),
    Line(100, 100, -100, 100),
    Line(-100, 100, -100, -100)*/
}
/*
Polygon::Polygon(QPolygon* qpoly){
    std::cout<<"Type of returned array: "<<typeid(qpoly->toStdVector()).name()<<std::endl;
    vector<QPoint> qpolyVector=qpoly->toStdVector();

    for (int i=0; i<qpolyVector.size()-1; i+=1)
        this->polygon.push_back(
            Line(qpolyVector.at(i).x(), qpolyVector.at(i).y(),
                 qpolyVector.at(i+1).x(), qpolyVector.at(i+1).y()));
    this->polygon.push_back(
        Line(qpolyVector.at(qpolyVector.size()-1).x(),
             qpolyVector.at(qpolyVector.size()-1).y(),
             qpolyVector.at(0).x(),
             qpolyVector.at(0).y()));
}
*/
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
