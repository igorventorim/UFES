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
	minPersonRadius = p->getRadius();
	maxPersonRadius = p->getRadius()*1.5;

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
	minPersonRadius = person->getRadius();
	maxPersonRadius = person->getRadius()*1.5;
}

void Stadium::drawStadium(void)
{

	glPushMatrix();
		glPushMatrix();
		glTranslatef(limitExterior->getCoord_x(),limitExterior->getCoord_y(),0);
		limitExterior->drawCircle();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(limitInterior->getCoord_x(),limitInterior->getCoord_y(),0);
		limitInterior->drawCircle();
		glPopMatrix();

		for (std::list<Circle*>::iterator circle=hightElements.begin(); circle != hightElements.end(); ++circle)
		{
 			glPushMatrix();
			glTranslatef((*circle)->getCoord_x(),(*circle)->getCoord_y(),0);
			  (*circle)->drawCircle();
			glPopMatrix();
		}

		for (std::list<Circle*>::iterator circle=lowElements.begin(); circle != lowElements.end(); ++circle)
		{
			glPushMatrix();
			glTranslatef((*circle)->getCoord_x(),(*circle)->getCoord_y(),0);
			  (*circle)->drawCircle();
			glPopMatrix();
		}

		glPushMatrix();
			glTranslatef(person->getCoord_x(), person->getCoord_y(), 0);
			person->drawCircle();
		glPopMatrix();
	glPopMatrix();
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
	if(personJumping)
	{
		if(limitInterior->circleInCircle(x,y,maxPersonRadius/1.5) || !limitExterior->circleInCircle(x,y,-maxPersonRadius/1.5) || inHightElements(x,y,maxPersonRadius/1.5))
		{	
			return false;
		}
		
	}else if(limitInterior->circleInCircle(x,y,minPersonRadius) || !limitExterior->circleInCircle(x,y,-minPersonRadius) || isInLowElements(x,y,minPersonRadius) || inHightElements(x,y,minPersonRadius))
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
	inLowElements = in;
}

bool Stadium::getInLowElements()
{
	double r;
	if(inLowElements)
	{
		r = person->getRadius()/1.5;
	}else
	{
		r = person->getRadius();
	}
	for (std::list<Circle*>::iterator circle=lowElements.begin(); circle != lowElements.end(); ++circle)
	{
		if((*circle)->circleInCircle(person->getCoord_x(),person->getCoord_y(),r))
		{
			return true;
		}
	}
	return false;
}

bool Stadium::getInLow()
{
	return inLowElements;
}

double Stadium::getMinPersonRadius()
{
	return minPersonRadius;
}
double Stadium::getMaxPersonRadius()
{
	return maxPersonRadius;
}