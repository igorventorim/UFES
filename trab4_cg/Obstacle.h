#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#include "Circle.h"

class Obstacle
{
	private:
		 Circle *element;
		 double height;
	public:
		Obstacle(Circle*,double);
		double getHeight(void);
		Circle* getElement(void);
		void draw(void);
};

#endif
