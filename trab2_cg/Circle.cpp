#include "Circle.h"

using namespace std;

Circle::Circle(int identificador, string cor, double raio)
{
    id = id;
    color = color;
    radius = radius;
}

Circle::Circle(int identificador, string cor, double raio, double dX, double dY)
{
    id = id;
    color = color;
    radius = raio;
    coord_x = dX;
    coord_y = dY;
}

Circle::Circle(int identificador,double raio ,double r,double g,double b)
{
    id = id;
    radius = raio;
    r_color = r;
    g_color = g;
    b_color = b;
}                


void Circle::setRadius(double r)
{
    radius = r;
}

void Circle::setColor(double c)
{
    color = c;
}

void Circle::setCoord_x(double x)
{
    coord_x = x;
}

void Circle::setCoord_y(double y)
{
    coord_y = y;
}

void Circle::setCenter(double x,double y)
{
    coord_x = x;
    coord_y = y;
}

double Circle::getRadius()
{
    return radius;
}

double Circle::getCoord_x()
{
    return coord_x;
}

double Circle::getCoord_y()
{
    return coord_y;
}

string Circle::getColor()
{
    return color;
}

double Circle::getRColor(void)
{
    return r_color;
}

double Circle::getGColor(void)
{
    return g_color;
}

double Circle::getBColor(void)
{
    return b_color;
}