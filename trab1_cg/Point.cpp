#include "Point.h"
#include <cmath>

Point::Point(void){}

Point::Point(double x, double y)
{
    coord_x = x;
    coord_y = y;
}

Point::Point(double x, double y, double z)
{
    coord_x = x;
    coord_y = y;
    coord_z = z;
}

double Point::getX(void)
{
    return coord_x;
}

double Point::getY(void)
{
    return coord_y;
}

double Point::getZ(void)
{
    return coord_z;
}

double Point::setX(double x)
{
    coord_x = x;
}

double Point::setY(double y)
{
    coord_y = y;
}

double Point::setZ(double z)
{
    coord_z = z;
}

double Point::setPoint2D(double x,double y)
{
    coord_x = x;
    coord_y = y;
}

double Point::setPoint3D(double x,double y,double z)
{
    coord_x = x;
    coord_y = y;
    coord_z = z;
}
double Point::distance2D(double x,double y)
{
   return sqrt(pow(getX()-x,2)+pow(getY()-y,2));
}

double Point::distance3D(double x,double y,double z)
{
    return sqrt(pow(getX()-x,2)+pow(getY()-y,2)+pow(getZ()-z,2));
}