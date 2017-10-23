#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <string>
#include "Point.h"
#include "Color.h"

class Rectangle
{
	private:
		int id;
		Color *color;
		Point *topLeft,*bottomLeft,*bottomRight,*topRight;
		Point *origin;
		double width,height;
		bool drawn;
	public:
		Rectangle(Color*,double,double);
		Rectangle(Color*,Point*,Point*,Point*,Point*);
		Rectangle(Point*,double,double,Color*);
		void setTopLeft(Point*);
		void setBottomLeft(Point*);
		void setBottomRight(Point*);
		void setTopRight(Point*);
        void drawRectangle(void);
        double getCoord_x(void);
        double getCoord_y(void);
        void setCoord_x(double);
        void setCoord_y(double);
        // void drawRectangle(double,double);
		bool isDrawn(void);

};
#endif