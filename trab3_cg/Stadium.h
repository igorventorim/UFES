#ifndef _STADIUM_H_
#define _STADIUM_H_

#include "Circle.h"
#include "Player.h"
#include <list>

class Stadium
{
	private:
		list<Circle*> objects;
		list<Circle*> hightElements;
		list<Circle*> lowElements;
		Circle *person;
		Player *player;
		Circle *limitExterior;
		Circle *limitInterior;
		bool personJumping;
		bool inLowElements;
		double minPersonRadius;
		double maxPersonRadius;
	public:
		Stadium(list<Circle*>,Circle*);
		Stadium(Circle*,Circle *, Circle *, list<Circle*>,list<Circle*>);
		Stadium(list<Circle*>,Player*);
		Stadium(Circle*,Circle *, Player *, list<Circle*>,list<Circle*>);
		void drawStadium(void);
		list<Circle*> getObjects(void);
		Circle* getPerson(void);
		Circle* getLimiteExterior(void);
		bool isValidMove(int);
		bool getPersonJumping(void);
		void setPersonJumping(bool);
		bool inHightElements(double, double,double);
		bool isInLowElements(double, double,double);
		bool setInLowElements(bool);
		bool getInLowElements(void);
		bool getInLow(void);
		double getMinPersonRadius(void);
		double getMaxPersonRadius(void);
		Player* getPlayer(void);

};

#endif
