#ifndef _STADIUM_H_
#define _STADIUM_H_

#include "Circle.h"
#include "Player.h"
#include "NPC.h"
#include <list>
#include "Shot.h"
#include "Obstacle.h"
#include <string>
#include "Color.h"
#include "Point.h"

class Stadium
{
	private:
		list<Circle*> objects;
		list<NPC*> NPCs;
		list<Obstacle*> obstacles;
		list<Shot*> shotsPlayer;
		list<Shot*> shotsNPC;
		Player *player;
		Circle *limitExterior;
		Circle *limitInterior;
		int score = 0;
		int MAX_SCORE;
		bool win = false;

	public:
		Stadium(list<Circle*>,Player*);
		Stadium(Circle*,Circle *, Player *, list<NPC*>,list<Obstacle*>);
		void drawStadium(void);

		Circle* getLimiteExterior(void);
		bool isValidMove(int);
		bool getPersonJumping(void);
		void setPersonJumping(bool);
		bool inHightElements(double, double,double);
		bool stopInObstacle(double, double,double);

		Player* getPlayer(void);
		static double MILLISECONDS_BY_FRAME;
		void addShotPlayer(Shot*);
		list<NPC*> getNPCs(void);
		bool checkShotPlayer(void);
		bool checkShotNPC(void);
		int getScore(void);
		void drawText(Color*,Point*,string);
		void setWin(bool);
		bool isWin(void);
		bool inObstacle(double, double, double);		

};

#endif
