#ifndef NPC_H
#define NPC_H


#include "Person.h"
#include "Circle.h"
#include "Point.h"
#include <vector>
#include <chrono>
#include <ctime>
// #include "Stadium.h"
// class Stadium;
// 

class NPC: public Person{

	private:
		Point* player;
		// Stadium* stadium;
		vector<int> current_movement;


	public:
		NPC(Circle*,double,double);
		void setPlayer(Point*);
		double movementEvaluate(vector<int>,int );
		double getAfterPersonAngle(int,int);
		void simulateLook(double,double,double,double&,double&);
		// void moveNPC(vector<int>,int);
		void setCurrentMovement(vector<int>);
		vector<int> getCurrentMovement(void);
		// void setStadium(Stadium*);

};

#endif