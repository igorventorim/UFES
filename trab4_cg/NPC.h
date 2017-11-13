#ifndef _NPC_H_
#define _NPC_H_
#include "Person.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Elipse.h"
#include "Point.h"
#include "Shot.h"
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;

class NPC: public Person{

	private:
		Point* player;

	public:
		NPC(Circle*,double,double);
		bool isMe(Person*);
		void setPlayer(Point*);
		int movementEvaluate(vector<int>,int );
		double getAfterPersonAngle(int,int);
		void simulateLook(double,double,double,double&,double&);
		void moveNPC(vector<int>,int);

};

#endif