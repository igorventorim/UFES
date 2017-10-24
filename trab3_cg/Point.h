#ifndef _POINT_H_
#define _POINT_H_
class Point
{
    private:
        double coord_x,coord_y,coord_z;
    public:
        Point(void);
        Point(double, double);
        Point(double, double, double);
        double getX(void);
        double getY(void);
        double getZ(void);
        double setX(double);
        double setY(double);
        double setZ(double);
        double setPoint2D(double,double);
        double setPoint3D(double,double,double);
        double distance2D(double,double);
        double distance3D(double,double,double);
        void moveX(double x);
        void moveY(double y);
};
#endif