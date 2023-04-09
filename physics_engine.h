#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H
//physics_engine.h
#include <iostream>
#include <vector>
#include <QPolygonF>
#include <QLineF>

class Point
{
public:
    double x, y;

    Point();
    Point(double _x, double _y);
    Point rotate(Point* center, double rad);
    Point rotateAround00(double rad);
    QPoint toQPoint();
    QPointF toQPointF();
    Point* move(double, double);
    Point stat_move(double, double);

    friend std::ostream & operator<<(std::ostream & out, Point & P){
        return out<<"("<<P.x<<";"<<P.y<<")";}
};

class Line_equation{
public:
    Line_equation();
    Line_equation(double, double);
    double k;
    double b;
};

class Line
{
public:
    Point p0, p1;
    Line_equation equation_of_self;
    Line_equation equation_of_perpendicular;

    Line();
    Line(Point _p0, Point _p1);
    Line(int _x0, int _y0, int _x1, int _y1);
    Line(double _x0, double _y0, double _x1, double _y1);
    QLineF to_qline();
    void find_equations(Point _electron);
    void find_equationOfSelf();
    void find_equationOfPerpendicular(Point _electron);
    double length();
    double square_of_length();
    int x0();
    int y0();
    int x1();
    int y1();

    int dx();
    int dy();

    friend std::ostream & operator<<(std::ostream & out, Line & L){
        return out<<L.p0<<"_"<<L.p1;}
    /*Line operator+(Line& add){
        this->p0.x+=add.dx();
        this->p1.x+=add.dx();
        this->p0.y-=add.dy();
        this->p1.y-=add.dy();
        return *this;
    }*/

    Line extendedCopy(int a){
        return Line(
            this->p0,
            Point(
                this->p1.x+(a-1)*this->dx(),
                this->p1.y-(a-1)*this->dy()));
    }

    Line movedCopy(Line* vector){
        return Line(
            this->p0.x+vector->dx(),
            this->p0.y-vector->dy(),
            this->p1.x+vector->dx(),
            this->p1.y-vector->dy());
    }

    Line movedCopy(Line staticVector){
        return Line(
            this->p0.x+staticVector.dx(),
            this->p0.y-staticVector.dy(),
            this->p1.x+staticVector.dx(),
            this->p1.y-staticVector.dy());
    }
};

class Polygon
{
public:
    std::vector<Line> polygon;

    Polygon();/*
    Polygon(QPolygon*);*/
    Polygon(std::vector<Line>);
    QPolygonF to_qpoly();

    friend std::ostream & operator<<(std::ostream & out, Polygon & Poly){
        for(Line l: Poly.polygon) out<<"<"<<l<<">  ";
        return out<<std::endl;}
};


class Physics_engine
{
public:
    Polygon metasurface_genuine;
    Line* interactive_surface=nullptr;
    Point electron_genuine;
    Point virt_genuine;

    double movementVectorStart_length();
    double movementTimeCounter_real;
    double movementTimeTotal_real;

    Point endpoint;

    double
        angle_V0_absolute,
        angle_surface_absolute,
        angle_V0_relative;

    double acceleration_mantissa, acceleration_exponent, acceleration;
    void calculate_acceleration();
    double get_acceleration_mantissa();
    int get_acceleration_exponent();

    static constexpr double PI=3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
    Physics_engine();

    static int mod_i(int);
    static double mod_d(double);
//    static Point vector_rotation_sin(Line l);
//    static Point vector_rotation_cos(Line l);
    static double radian(double angle);
    static double angle(double radian);

    Line scaleVector(Point p0, Point p1, double);

    Point base_of_perpendicular;
    void find_base_of_perpendicular(Line);
    /*Point kollision; //you can`t return NULL to object, and i don`t want to use pointer
    bool findProjection(Point, Line);
    bool findKollision(Line moving, Line surface_line);*/
};

#endif // PHYSICS_ENGINE_H
