#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <iostream>

class Point;
class Line;

class Physics_engine
{
public:
    Physics_engine();
    void change_particle_position(double dx, double dy);
    void recalculate(double time);
    Point *intersection;
    bool check_kollision(Line moving, Line surface_line);
};

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
    int x0();
    int y0();
    int x1();
    int y1();

    friend std::ostream & operator<<(std::ostream & out, Line & L);
};


#endif // PHYSICS_ENGINE_H
/*

class Vector
{
public:
    Point p;
    Vector();
    Vector(Point _p0, Point _p1);
    Vector(int _x0, int _y0, int _x1, int _y1);
    double angle(Vector v0, Vector v1);
    int x();
    int y();
};

*/
