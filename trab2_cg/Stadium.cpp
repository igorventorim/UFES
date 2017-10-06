#include "Stadium.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>


Stadium::Stadium(list<Circle*> o,Circle* p)
{
	objects = o;
	person = p;
	personJumping = false;
	setInLowElements(false);

}

Stadium::Stadium(Circle* exterior, Circle *inferior, Circle *psn, list<Circle*> hight, list<Circle*>low)
{
	limitExterior = exterior;
	limitInterior = inferior;
	person = psn;
	hightElements = hight;
	lowElements = low;
	personJumping = false;
	setInLowElements(false);
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

	double r = person->getRadius();
	// if(limitInterior->circleInCircle(x,y,r))
	// {
	// 	return false;
	// }else if(!limitExterior->circleInCircle(x,y,-r))
	// {
	// 	return false;
	// }else if(inHightElements(x,y))
	// {
	// 	return false;
	// }else if(inLowElements(x,y) && !personJumping)
	// {
	// 	return false;
	// }
	if(personJumping)
	{
		if(limitInterior->circleInCircle(x,y,r/1.5) || !limitExterior->circleInCircle(x,y,-r/1.5) || inHightElements(x,y,r/1.5))
		{	
			return false;
		}
		
	}else if(limitInterior->circleInCircle(x,y,r) || !limitExterior->circleInCircle(x,y,-r) || isInLowElements(x,y,r) || inHightElements(x,y,r))
	{
		return false;
	}

	return true;
}

bool Stadium::inHightElements(double x, double y, double r)
{
	for (std::list<Circle*>::iterator circle=hightElements.begin(); circle != hightElements.end(); ++circle)
	{
	  if((*circle)->circleInCircle(x,y,r))
	  {
		  return true;
	  }
	}
	return false;
}

bool Stadium::isInLowElements(double x, double y, double r)
{

	for (std::list<Circle*>::iterator circle=lowElements.begin(); circle != lowElements.end(); ++circle)
	{
		if((*circle)->circleInCircle(x,y,r) && !(*circle)->circleInCircle(person->getCoord_x(),person->getCoord_y(),r))
		{
			return true;
		}
	}
	return false;
}


bool Stadium::setInLowElements(bool in)
{
	if(in)
	{
		cout << "Entrei\n";
	}
	inLowElements = in;
}

bool Stadium::getInLowElements()
{
	return inLowElements;
}