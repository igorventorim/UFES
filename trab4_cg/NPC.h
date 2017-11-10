#ifndef _NPC_H_
#define _NPC_H_
#include "Person.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Elipse.h"
#include "Point.h"
#include "Shot.h"
#include <chrono>
#include <ctime>



class NPC: public Person{

	private:

	public:
		NPC(Circle*,double,double);
		bool isMe(Person*);

};

#endif