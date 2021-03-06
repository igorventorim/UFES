#ifndef _ELIPSE_H_
#define _ELIPSE_H_
#include "Point.h"
#include <string>
#include "Color.h"
using namespace std;
class Elipse{
    private:
      int id;
      // string color;
      double radiusA;
      double radiusB;
      // double r_color,g_color,b_color;
      Color* color;
      bool drawn;
      Point *center; 
    public:
      Elipse(double,double);
      Elipse(double,double,Point*,Color*);
      // double getRColor(void);
      // double getGColor(void);
      // double getBColor(void);
      // void setRColor(double);
      // void setGColor(double);
      // void setBColor(double);
      void setColor(Color*);
      Color *getColor(void);
      void setCenter(Point*);
      Point* getCenter(void);
      bool isDrawn(void);
      void drawElipse(void);
      double getCoord_x(void);
      double getCoord_y(void);
      void setCoord_x(double);
      void setCoord_y(double);
};
#endif
