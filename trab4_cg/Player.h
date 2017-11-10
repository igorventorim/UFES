#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Person.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Elipse.h"
#include "Point.h"
#include "Shot.h"
#include <chrono>
#include <ctime>

using namespace std;

class Player: public Person
{
	private:


	public:
		Player(Circle*,double,double);


};
#endif