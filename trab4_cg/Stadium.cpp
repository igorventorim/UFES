
#include "Stadium.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <cstring>
#include <iostream>

using namespace std;
double Stadium::MILLISECONDS_BY_FRAME = 0;

Stadium::Stadium(list<Circle*> o,Player *p)
{
	objects = o;
	player = p;
}

Stadium::Stadium(Circle* exterior, Circle *inferior, Player *p, list<NPC*> npcs, list<Obstacle*>obst, double freqShot)
{
	limitExterior = exterior;
	limitInterior = inferior;
	player = p;
	NPCs = npcs;
	obstacles = obst;
	MAX_SCORE = npcs.size();
	freqShotNPC = freqShot;
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
			(*npc)->draw();
		}

		for (std::list<Obstacle*>::iterator obstacle=obstacles.begin(); obstacle != obstacles.end(); ++obstacle)
		{
			(*obstacle)->draw();
		}

		for (std::list<Shot*>::iterator shot=shotsPlayer.begin(); shot != shotsPlayer.end(); ++shot)
		{
			(*shot)->draw();
		}

		for (std::list<Shot*>::iterator shot=shotsNPC.begin(); shot != shotsNPC.end(); ++shot)
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

bool Stadium::getPersonJumping(Person* p)
{
	return p->isJumping();
}

void Stadium::setPersonJumping(bool jump,Person* p)
{
	p->setJumping(jump);
}

bool Stadium::isValidMove(int c,Person *p)
{
	double x,y;
	x = p->getAfterX(c);
	y = p->getAfterY(c);

	double r = p->getRadius();

	if(limitInterior->circleInCircle(x,y,r) || !limitExterior->circleInCircle(x,y,-r) || stopInObstacle(p,x,y,r)  || inNPC(x,y,r,p))
	{
		return false;
	}

	if(!inObstacle(x,y,r) && p->isOnElement())
	{
		p->setOnElement(false);
	}

	return true;
}

bool Stadium::inNPC(double x, double y, double r, Person *p)
{
	for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
	{
	  if((*npc)->getHead()->circleInCircle(x,y,r) && !(*npc)->isMe(p) )
	  {
		  return true;
	  }
	}
	return false;
}

bool Stadium::stopInObstacle(Person* p,double x, double y, double r)
{

		for (std::list<Obstacle*>::iterator obstacle=obstacles.begin(); obstacle != obstacles.end(); ++obstacle)
		{
			if((*obstacle)->getElement()->circleInCircle(x,y,r))
			{
				if(getPersonJumping(p))
				{
					// cout << (player->getScale() - 1)  << "\n";
					if(p->getScale() - 1 > (*obstacle)->getHeight() * (p->getScaleInit()/2) )
					{
						p->setHeightOnObstacle((*obstacle)->getHeight());
						p->setOnElement(true);
						return false;
					}else 
					{
						return true;
					}
				}else
				{
					return true;
				}
			}
		}
	
	return false;
}

bool Stadium::inObstacle(double x, double y, double r)
{
	for (std::list<Obstacle*>::iterator obstacle=obstacles.begin(); obstacle != obstacles.end(); ++obstacle)
	{
		if((*obstacle)->getElement()->circleInCircle(x,y,r))
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

void Stadium::addShotPlayer(Shot* s)
{
	shotsPlayer.push_back(s);
}

void Stadium::addShotNPC(Shot* s)
{
	shotsNPC.push_back(s);
}


list<NPC*> Stadium::getNPCs(void)
{
	return NPCs;
}

bool Stadium::checkShotPlayer(void)
{
	for (std::list<Shot*>::iterator shot=shotsPlayer.begin(); shot != shotsPlayer.end(); ++shot)
	{
		Circle* c = (*shot)->getShot();

		if(!limitExterior->circleInCircle(c->getCoord_x(),c->getCoord_y(),c->getRadius()))
		{
			shotsPlayer.erase(shot++);
			continue;
		}

		if(limitInterior->circleInCircle(c->getCoord_x(),c->getCoord_y(),c->getRadius()))
		{
			shotsPlayer.erase(shot++);
			continue;
		}

		for (std::list<Obstacle*>::iterator obstacle=obstacles.begin(); obstacle != obstacles.end(); ++obstacle)
		{
			if((*obstacle)->getElement()->circleInCircle(c->getCoord_x(),c->getCoord_y(),c->getRadius()))
			{
				shotsPlayer.erase(shot++);
				continue;
			}
		}

		for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
		{
			Point* p = (*npc)->getCenter();
			if (c->circleInCircle(p->getX(),p->getY(),player->getRadius()))
			{
					score++;
					NPCs.erase(npc++);
					shotsPlayer.erase(shot++);
			}
		}
	}

	if(score == MAX_SCORE)
	{
		return true;
	}else
	{
		return false;
	}
}

bool Stadium::checkShotNPC(void)
{
	
	for (std::list<Shot*>::iterator shot=shotsNPC.begin(); shot != shotsNPC.end(); ++shot)
	{
		Circle* c = (*shot)->getShot();

		if(!limitExterior->circleInCircle(c->getCoord_x(),c->getCoord_y(),c->getRadius()))
		{
			shotsNPC.erase(shot++);
			continue;
		}

		if(limitInterior->circleInCircle(c->getCoord_x(),c->getCoord_y(),c->getRadius()))
		{
			shotsNPC.erase(shot++);
			continue;
		}

		for (std::list<Obstacle*>::iterator obstacle=obstacles.begin(); obstacle != obstacles.end(); ++obstacle)
		{
			if((*obstacle)->getElement()->circleInCircle(c->getCoord_x(),c->getCoord_y(),c->getRadius()))
			{
				shotsNPC.erase(shot++);
				continue;
			}
		}

		Point* p = player->getCenter();
		if (c->circleInCircle(p->getX(),p->getY(),player->getRadius()))
		{
			shotsNPC.erase(shot++);
			return true; 
		}
	}

	return false;
}

int Stadium::getScore(void)
{
	return score;
}

void Stadium::drawText(Color* c,Point *p, string s)
{
	glColor3f( c->getRColor(), c->getGColor(), c->getBColor() );
	glRasterPos2f( p->getX(), p->getY() );
	int j = strlen( s.c_str() );
	for( int i = 0; i < j; i++ ) {
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, s.c_str()[i] );
	}
}

void Stadium::setWin(bool value)
{
	win = value;
}
bool Stadium::isWin(void)
{
	return win;
}

double Stadium::getFreqShotNPC(void)
{
	return freqShotNPC;
}

void Stadium::shootShotsNPCs(void)
{
	for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
	{
		addShotNPC((*npc)->atirar());		
	}
}