#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include <string>
#include "Point.h"
using namespace std;
class Circle
{
    private:
        int id;
        string color;
        double radius;//,coord_x,coord_y;
        double r_color,g_color,b_color;
        bool drawn, update;
        Point center;

    public:
        Circle(int,string,double);
        Circle(int,string,double,double,double);
        Circle(int,double,double,double,double);
        void setRadius(double);
        void setColor(double);
        // void setCoord_x(double);
        // void setCoord_y(double);
        void setCenter(double,double);
        double getRadius(void);
        // double getCoord_x(void);
        // double getCoord_y(void);
        string getColor(void);
        double getRColor(void);
        double getGColor(void);
        double getBColor(void);
        bool isDrawn(void);
        void drawCircle(void);
        void setDrawn(bool);
        double distance2Center(double,double);
        bool pointInCircle(double, double);
        void setUpdate(bool);
        bool getUpdate(void);
        Point getCenter(void);

};
#endif
