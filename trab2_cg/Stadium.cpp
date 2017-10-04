#include "Stadium.h"


Stadium::Stadium(list<Circle*> o,Circle* p)
{
	objects = o;
	person = p;

}

void Stadium::drawStadium(void)
{

 	// glClear (GL_COLOR_BUFFER_BIT);
	for (std::list<Circle*>::iterator circle=objects.begin(); circle != objects.end(); ++circle)
	{
	  (*circle)->drawCircle();
	}

	person->drawCircle();

}

list<Circle*> Stadium::getObjects(void)
{
	return objects;
}

Circle* Stadium::getPerson(void)
{
	return person;
}