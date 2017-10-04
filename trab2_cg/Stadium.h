#ifndef _STADIUM_H_
#define _STADIUM_H_
#include "Circle.h"
#include <list>

class Stadium
{
	private:
		list<Circle*> objects;
		list<Circle*> hightElements;
		list<Circle*> lowElements;
		Circle *person;
		Circle *limitExterior;
		Circle *limitInterior;
	public:
		Stadium(list<Circle*>,Circle*);
		Stadium(Circle*,Circle *, Circle *, list<Circle*>,list<Circle*>);
		void drawStadium(void);
		list<Circle*> getObjects(void);
		Circle* getPerson(void);
		Circle* getLimiteExterior(void);

};

#endif
