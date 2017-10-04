#include "Stadium.h"


Stadium::Stadium(list<Circle*> o,Circle* p)
{
	objects = o;
	person = p;

}

Stadium::Stadium(Circle* exterior, Circle *inferior, Circle *psn, list<Circle*> hight, list<Circle*>low)
{
	limitExterior = exterior;
	limitInterior = inferior;
	person = psn;
	hightElements = hight;
	lowElements = low;
}

void Stadium::drawStadium(void)
{

 	// glClear (GL_COLOR_BUFFER_BIT);

	limitExterior->drawCircle();
	limitInterior->drawCircle();

	for (std::list<Circle*>::iterator circle=hightElements.begin(); circle != hightElements.end(); ++circle)
	{
	  (*circle)->drawCircle();
	}

	for (std::list<Circle*>::iterator circle=lowElements.begin(); circle != lowElements.end(); ++circle)
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

Circle* Stadium::getLimiteExterior(void)
{
	return limitExterior;
}
