#ifndef _ELIPSE_H_
#define _ELIPSE_H_
#include "Point.h"
#include <string>
using namespace std;
class Elipse{
    private:
      int id;
      string color;
      double radiusA;
      double radiusB;
      double r_color,g_color,b_color;
      bool drawn;
      Point *center; 
    public:
      Elipse(double,double);
      Elipse(double,double,Point*,double,double,double);
      double getRColor(void);
      double getGColor(void);
      double getBColor(void);
      void setRColor(double);
      void setGColor(double);
      void setBColor(double);
      void setCenter(Point*);
      Point* getCenter(void);
      bool isDrawn(void);
      void drawElipse(void);
};
#endif
