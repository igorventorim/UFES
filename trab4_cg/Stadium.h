#ifndef _STADIUM_H_
#define _STADIUM_H_

#include "Circle.h"
#include "Player.h"
#include "NPC.h"
#include <list>
#include "Shot.h"

class Stadium
{
	private:
		list<Circle*> objects;
		list<NPC*> NPCs;
		list<Circle*> lowElements;
		list<Shot*> shots;
		// Circle *person;
		Player *player;
		Circle *limitExterior;
		Circle *limitInterior;
		// bool personJumping;
		// bool inLowElements;
		// double minPersonRadius;
		// double maxPersonRadius;
	public:
		// Stadium(list<Circle*>,Circle*);
		// Stadium(Circle*,Circle *, Circle *, list<Circle*>,list<Circle*>);
		Stadium(list<Circle*>,Player*);
		Stadium(Circle*,Circle *, Player *, list<NPC*>,list<Circle*>);
		void drawStadium(void);
		// list<Circle*> getObjects(void);
		// Circle* getPerson(void);
		Circle* getLimiteExterior(void);
		bool isValidMove(int);
		bool getPersonJumping(void);
		void setPersonJumping(bool);
		bool inHightElements(double, double,double);
		bool isInLowElements(double, double,double);
		// bool setInLowElements(bool);
		// bool getInLowElements(void);
		// bool getInLow(void);
		// double getMinPersonRadius(void);
		// double getMaxPersonRadius(void);
		Player* getPlayer(void);
		static double MILLISECONDS_BY_FRAME;
		void addShot(Shot*);

		// static void setMillisecondsByFrame(double);

};

#endif
