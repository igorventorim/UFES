
#include "Stadium.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>


Stadium::Stadium(list<Circle*> o,Player *p)
{
	objects = o;
	player = p;
	p->setJumping(false);
	setInLowElements(false);
	minPersonRadius = p->getHeadRadius();
	maxPersonRadius = p->getHeadRadius()*1.5;
}

Stadium::Stadium(Circle* exterior, Circle *inferior, Player *p, list<Circle*> hight, list<Circle*>low)
{
	limitExterior = exterior;
	limitInterior = inferior;
	player = p;
	hightElements = hight;
	lowElements = low;
	p->setJumping(false);
	setInLowElements(false);
	minPersonRadius = p->getHeadRadius();
	maxPersonRadius = p->getHeadRadius()*1.5;
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

		player->draw();

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
	return player->isJumping();
}

void Stadium::setPersonJumping(bool jump)
{
	player->setJumping(jump);
}

bool Stadium::isValidMove(int c)
{
	double x,y;
	x = player->getAfterX(c);
	y = player->getAfterY(c);

	double r = player->getRadius();
	if(getPersonJumping())
	{
		if(limitInterior->circleInCircle(x,y,maxPersonRadius/1.5) || !limitExterior->circleInCircle(x,y,-maxPersonRadius/1.5) || inHightElements(x,y,maxPersonRadius/1.5))
		{	
			return false;
		}
		
	}else if(limitInterior->circleInCircle(x,y,/*minPersonRadius*/r) || !limitExterior->circleInCircle(x,y,-r/*minPersonRadius*/) || isInLowElements(x,y,r/*minPersonRadius*/) || inHightElements(x,y,/*minPersonRadius*/r))
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
		if((*circle)->circleInCircle(x,y,r) && !(*circle)->circleInCircle(player->getCoord_x(),player->getCoord_y(),r))
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

bool Stadium::getInLowElements(void)
{
	double r;
	if(inLowElements)
	{
		r = player->getRadius()/1.5;
	}else
	{
		r = player->getRadius();
	}
	for (std::list<Circle*>::iterator circle=lowElements.begin(); circle != lowElements.end(); ++circle)
	{
		if((*circle)->circleInCircle(player->getCoord_x(),player->getCoord_y(),r))
		{
			return true;
		}
	}
	return false;
}

bool Stadium::getInLow(void)
{
	return inLowElements;
}

double Stadium::getMinPersonRadius(void)
{
	return minPersonRadius;
}
double Stadium::getMaxPersonRadius(void)
{
	return maxPersonRadius;
}

Player* Stadium::getPlayer(void)
{
	return player;
}