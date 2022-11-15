#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H
//physics_engine.h
#include <iostream>
#include <vector>
#include <QPolygonF>
#include <QLineF>

class Point;
class Line;

class Point
{
public:
    int x, y;

    Point();
    Point(int _x, int _y);

    friend std::ostream & operator<<(std::ostream & out, Point & P);
};

class Line
{
public:
    Point p0, p1;

    Line();
    Line(Point _p0, Point _p1);
    Line(int _x0, int _y0, int _x1, int _y1);
    QLineF to_qline();
    int x0();
    int y0();
    int x1();
    int y1();

    friend std::ostream & operator<<(std::ostream & out, Line & L);
};

class Polygon
{
public:
    std::vector<Line> polygon;

    Polygon();
    Polygon(std::vector<Line>);
    QPolygonF to_qpoly();

    friend std::ostream & operator<<(std::ostream & out, Polygon & Poly);
};

class Physics_engine
{
public:
    Polygon metasurface_genuine;
    Point electron_genuine;
    Line movementVector_genuine;

    const double PI=3.14159265358979323846;
    Physics_engine();
    void change_particle_position(double dx, double dy);
    void recalculate(double time);
    Line rotateVector(Point p0, Point p1, int);
    Line scaleVector(Point p0, Point p1, double);

    Point projection;
    Point kollision; //you can`t return NULL to object, and i don`t want to use pointer
    bool findProjection(Point, Line);
    bool findKollision(Line moving, Line surface_line);
};

#endif // PHYSICS_ENGINE_H
