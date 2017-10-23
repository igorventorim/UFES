#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <string>
#include "Point.h"

class Rectangle
{
	private:
		int id;
		double r_color,g_color,b_color;
		Point *topLeft,*bottomLeft,*bottomRight,*topRight;
		double width,height;
		bool drawn;
	public:
		Rectangle(double,double,double,double,double);
		Rectangle(double,double,double,Point*,Point*,Point*,Point*);
		void setTopLeft(Point*);
		void setBottomLeft(Point*);
		void setBottomRight(Point*);
		void setTopRight(Point*);
        double getRColor(void);
        double getGColor(void);
        double getBColor(void);
        void drawRectangle();
        // void drawRectangle(double,double);
		bool isDrawn(void);

};
#endif