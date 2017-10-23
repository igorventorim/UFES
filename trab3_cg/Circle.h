#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include <string>
#include "Point.h"
#include "Color.h"
using namespace std;
class Circle
{
    private:
        int id;
        Color* color;
        double radius;//,coord_x,coord_y;
        // double r_color,g_color,b_color;
        bool drawn, update;
        Point center;
        void colornameToRGB(string colorname);
    public:
        Circle(int,Color*,double);
        Circle(int,Color*,double,double,double);
        Circle(int,double,Color*);
        void setRadius(double);
        void setColor(Color*);
        void setCoord_x(double);
        void setCoord_y(double);
        void moveX(double);
        void moveY(double);
        void setCenter(double,double);
        double getRadius(void);
        double getCoord_x(void);
        double getCoord_y(void);
        Color* getColor(void);
        // double getRColor(void);
        // double getGColor(void);
        // double getBColor(void);
        bool isDrawn(void);
        void drawCircle(void);
        void setDrawn(bool);
        double distance2Center(double,double);
        bool pointInCircle(double, double);
        void setUpdate(bool);
        bool getUpdate(void);
        int getId(void);
        Point getCenter(void);
        void move(void);
        bool circleInCircle(double , double , double );

};
#endif
