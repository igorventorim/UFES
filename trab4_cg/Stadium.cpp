
#include "Stadium.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <cstring>
#include <iostream>
#include "NPC.h"

using namespace std;
double Stadium::MILLISECONDS_BY_FRAME = 0;

Stadium::Stadium(Circle* exterior, Circle *inferior, Player *p, list<NPC*> npcs, list<Obstacle*>obst, double freqShot)
{
	limitExterior = exterior;
	limitInterior = inferior;
	player = p;
	NPCs = npcs;
	obstacles = obst;
	MAX_SCORE = npcs.size();
	freqShotNPC = freqShot;

	for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
	{
		(*npc)->setPlayer(p->getCenter());
		// (*npc)->setStadium(this);
	}

	// ga = new GeneticAlgorithm();

	NPC::stadium = this;
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


		for (std::list<Obstacle*>::iterator obstacle=obstacles.begin(); obstacle != obstacles.end(); ++obstacle)
		{
			(*obstacle)->draw();
		}

		for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
		{
			(*npc)->draw();
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
	x = p->getAfterX(c,p->getPersonAngle());
	y = p->getAfterY(c,p->getPersonAngle());

	double r = p->getRadius();

	if(limitInterior->circleInCircle(x,y,r) || !limitExterior->circleInCircle(x,y,-r) || stopInObstacle(p,x,y,r)  || inNPC(x,y,r,p) || (inPlayer(x,y,r) && !player->isMe(p)))
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

bool Stadium::inPlayer(double x, double y, double r)
{
	if(player->getHead()->circleInCircle(x,y,r) )
	{
		return true;
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
			if (c->circleInCircle(p->getX(),p->getY(),player->getRadius()) && !(*npc)->isOnElement())
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
		if (c->circleInCircle(p->getX(),p->getY(),player->getRadius()) && !player->isOnElement())
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
		if(!(*npc)->isOnElement() && !(*npc)->isJumping() )
		{
			addShotNPC((*npc)->atirar());
		}
				
	}
}

void Stadium::moveNPC(void)
{
	// ga->run(NPCs);
	// ga->modifyRun(NPCs);

	for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
	{

		// moveNPC((*npc));
		if(nextToObstacle((*npc)))
		{
			(*npc)->jump();
		}

		if ((*npc)->getCurrentMovement()[3]
		&& isValidMove(-1,(*npc))){
			(*npc)->setDown(true);
			(*npc)->moveDown();
		}

		if (((*npc))->getCurrentMovement()[1]) {
			(*npc)->rotateLeft();
		}

		if (((*npc))->getCurrentMovement()[0]) {
			(*npc)->rotateRight();
		}

		if (((*npc))->getCurrentMovement()[2]
				&& isValidMove(1,(*npc))) {
			(*npc)->moveUp();
		}

		// if (((*npc))->getCurrentMovement()[4]) {
		// 	(*npc)->jump();
		// }

		if((*npc)->isJumping() || (*npc)->getResize() || (*npc)->isJumpingOnElement())
		{
			(*npc)->changeSize();
		}


		(*npc)->setDown(false);
	}
}

bool Stadium::nextToObstacle(NPC* npc)
{
	double x,y;
	x = npc->getCoord_x();
	y = npc->getCoord_y();
		for (std::list<Obstacle*>::iterator obstacle=obstacles.begin(); obstacle != obstacles.end(); ++obstacle)
		{
			if((*obstacle)->getElement()->distance2Center(x,y) < (*obstacle)->getElement()->getRadius()+ 2*npc->getHead()->getRadius() )
			{
				return true;
			}
		}

		return false;

}

void Stadium::changeSizeNPCs(void)
{

	for (std::list<NPC*>::iterator npc=NPCs.begin(); npc != NPCs.end(); ++npc)
	{
		if((*npc)->isJumping() || (*npc)->getResize() || (*npc)->isJumpingOnElement())
		{
			(*npc)->changeSize();
		}
	}

}