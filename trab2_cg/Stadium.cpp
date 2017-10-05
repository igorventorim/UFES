#include "Stadium.h"
#include <GL/gl.h>
#include <GL/glu.h>


Stadium::Stadium(list<Circle*> o,Circle* p)
{
	objects = o;
	person = p;
	personJumping = false;

}

Stadium::Stadium(Circle* exterior, Circle *inferior, Circle *psn, list<Circle*> hight, list<Circle*>low)
{
	limitExterior = exterior;
	limitInterior = inferior;
	person = psn;
	hightElements = hight;
	lowElements = low;
	personJumping = false;
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

bool Stadium::getPersonJumping(void)
{
	return personJumping;
}

void Stadium::setPersonJumping(bool jump)
{
	personJumping = jump;
}

bool Stadium::isValidMove(double x,double y)
{
	if(limitInterior->circleInCircle(x,y,person->getRadius()))
	{
		return false;
	}else if(!limitExterior->circleInCircle(x,y,-person->getRadius()))
	{
		return false;
	}else if(inHightElements(x,y))
	{
		return false;
	}else if(inLowtElements(x,y) && !personJumping)
	{
		return false;
	}
	return true;
}

bool Stadium::inHightElements(double x, double y)
{
	for (std::list<Circle*>::iterator circle=hightElements.begin(); circle != hightElements.end(); ++circle)
	{
	  if((*circle)->circleInCircle(x,y,person->getRadius()))
	  {
		  return true;
	  }
	}
	return false;
}

bool Stadium::inLowtElements(double x, double y)
{

	for (std::list<Circle*>::iterator circle=lowElements.begin(); circle != lowElements.end(); ++circle)
	{
		if((*circle)->circleInCircle(x,y,person->getRadius()) && !(*circle)->circleInCircle(person->getCoord_x(),person->getCoord_y(),person->getRadius()) )
		{
			return true;
		}
	}
	return false;
}