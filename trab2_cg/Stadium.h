#ifndef _STADIUM_H_
#define _STADIUM_H_
#include "Circle.h"
#include <list>

class Stadium
{
	private:
		list<Circle*> objects;
		Circle *person;
	public:
		Stadium(list<Circle*>,Circle*);
		void drawStadium(void);
		list<Circle*> getObjects(void);

};

#endif