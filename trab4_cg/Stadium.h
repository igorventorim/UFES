#ifndef STADIUM_H
#define STADIUM_H


#include "NPC.h"
#include "Circle.h"
#include "Player.h"
#include <list>
#include "Shot.h"
#include "Obstacle.h"
#include <string>
#include "Color.h"
#include "Point.h"
// #include "GeneticAlgorithm.h"

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
		double freqShotNPC;
		int score = 0;
		int MAX_SCORE;
		bool win = false;
		// GeneticAlgorithm *ga;

	public:
		Stadium(Circle*,Circle *, Player *, list<NPC*>,list<Obstacle*>,double);
		void drawStadium(void);
		Circle* getLimiteExterior(void);
		bool isValidMove(int,Person *);
		bool getPersonJumping(Person*);
		void setPersonJumping(bool,Person*);
		bool inNPC(double, double,double, Person*);
		bool stopInObstacle(Person*,double, double,double);
		Player* getPlayer(void);
		void addShotNPC(Shot* s);
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
		double getFreqShotNPC(void);
		void shootShotsNPCs(void);
		// void moveNPC(void);
		void changeSizeNPCs(void);
		bool isValidMoveNPC(Person*,double, double);
		bool inPlayer(double x, double y, double r);

};

#endif
