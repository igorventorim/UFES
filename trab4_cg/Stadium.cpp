
#include "Stadium.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

double Stadium::MILLISECONDS_BY_FRAME = 0;

Stadium::Stadium(list<Circle*> o,Player *p)
{
	objects = o;
	player = p;
	// p->setJumping(false);
	// setInLowElements(false);
	// minPersonRadius = p->getHeadRadius();
	// maxPersonRadius = p->getHeadRadius()*1.5;
}

Stadium::Stadium(Circle* exterior, Circle *inferior, Player *p, list<NPC*> npcs, list<Circle*>low)
{
	limitExterior = exterior;
	limitInterior = inferior;
	player = p;
	NPCs = npcs;
	lowElements = low;
	// p->setJumping(false);
	// setInLowElements(false);
	// minPersonRadius = p->getHeadRadius();
	// maxPersonRadius = p->getHeadRadius()*1.5;
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

		for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
		{
 		// 	glPushMatrix();
			// glTranslatef((*circle)->getCoord_x(),(*circle)->getCoord_y(),0);
			//   (*circle)->drawCircle();
			// glPopMatrix();
			(*npc)->draw();
		}

		for (std::list<Circle*>::iterator circle=lowElements.begin(); circle != lowElements.end(); ++circle)
		{
			glPushMatrix();
			glTranslatef((*circle)->getCoord_x(),(*circle)->getCoord_y(),0);
			  (*circle)->drawCircle();
			glPopMatrix();
		}

		for (std::list<Shot*>::iterator shot=shots.begin(); shot != shots.end(); ++shot)
		{
			(*shot)->draw();
		}

		player->draw();

	glPopMatrix();
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
	if(getPersonJumping() )
	{
		if(limitInterior->circleInCircle(x,y,r) || !limitExterior->circleInCircle(x,y,-r) || inHightElements(x,y,r))
		{
			return false;
		}
	}else
	if(limitInterior->circleInCircle(x,y,r) || !limitExterior->circleInCircle(x,y,-r) || isInLowElements(x,y,r) || inHightElements(x,y,r))
	{
		return false;
	}

	if(isInLowElements(x,y,r))
	{
		player->setOnElement(true);
	}
	else if(!isInLowElements(x,y,r)){

		if(player->isOnElement())
		{
			player->setJumping(false);
		}
		player->setOnElement(false);


	}

	return true;
}

bool Stadium::inHightElements(double x, double y, double r)
{
	for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
	{
	  if((*npc)->getHead()->circleInCircle(x,y,r))
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
		if((*circle)->circleInCircle(x,y,r) /*&& !(*circle)->circleInCircle(player->getCoord_x(),player->getCoord_y(),r)*/)
		{
			return true;
		}
	}
	return false;
}

Player* Stadium::getPlayer(void)
{
	return player;
}

void Stadium::addShot(Shot* s)
{
	shots.push_back(s);
}
