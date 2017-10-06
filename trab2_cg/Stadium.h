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
		bool personJumping;
		bool inLowElements;
	public:
		Stadium(list<Circle*>,Circle*);
		Stadium(Circle*,Circle *, Circle *, list<Circle*>,list<Circle*>);
		void drawStadium(void);
		list<Circle*> getObjects(void);
		Circle* getPerson(void);
		Circle* getLimiteExterior(void);
		bool isValidMove(double,double);
		bool getPersonJumping(void);
		void setPersonJumping(bool);
		bool inHightElements(double, double,double);
		bool isInLowElements(double, double,double);
		bool setInLowElements(bool);
		bool getInLowElements();
		bool getInLow();

};

#endif
