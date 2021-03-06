#include "NPC.h"
#include <iostream>
#include <cmath>
#include "Stadium.h"

Stadium* NPC::stadium = NULL;

NPC::NPC(Circle* circle, double shot, double move): Person(circle,shot,move){}

double NPC::getAfterPersonAngle(int right,int left)
{
	double after_person_angle = getPersonAngle();

	if(right)
	{
		if(getDown())
		{
			after_person_angle += getUpdateVelocityPerson();
		}else
		{
			after_person_angle -= getUpdateVelocityPerson();
		}
	}

	if(left)
	{
		if(getDown())
		{
			after_person_angle -= getUpdateVelocityPerson();
		}else
		{
			after_person_angle += getUpdateVelocityPerson();
		}
	}

	return after_person_angle;
}

void NPC::simulateLook(double centerX, double centerY, double personAngle, double& lookX,double& lookY)
{
    double x0=getRadius()+getRadiusShoulderA()/2;
    double y0=getHeightHand();
    lookX = x0 * cos(personAngle*M_PI/180) - y0 * sin(personAngle*M_PI/180) + centerX;
    lookY = x0 * sin(personAngle*M_PI/180) + y0 * cos(personAngle*M_PI/180) + centerY;
}

void NPC::setPlayer(Point *p)
{
	player = p;
}


/*
	POSITION 0: ROTATE RIGHT
	POSITION 1: ROTATE LEFT
	POSITION 2: MOVE UP
	POSITION 3: MOVE DOWN
	POSITION 4: JUMP
*/
double NPC::movementEvaluate(vector<int> individual,int size_vector)
{
	srand(time(NULL));
	Stadium* stadium = NPC::stadium;
	Circle *c = stadium->getLimiteExterior();
	double playerX = player->getX();
	double playerY = player->getY();
	double score = 0;
	double afterAngle = 0;
	// double angle = atan2(playerY, playerX ) - atan2(getCoord_y(), getCoord_y()); 
	double afterX = getCenter()->getX();
	double afterY = getCenter()->getY();
	double current_distance = player->distance2D(afterX,afterY);

	// if(individual[0] == 1)
	// {
	// 	afterAngle = getAfterPersonAngle(1,0);
	// 	// score +=4;
	// 	score++;
		
	// }
	// if(individual[1] == 1)
	// {
	// 	afterAngle = getAfterPersonAngle(0,1);
	// 	score++;
	// }
	
	if(individual[2] == 1)
	{
    	// afterX = getAfterX(1,0);
    	// afterY = getAfterY(1,0);
		score += 3;
		// score++;
	}

	if(individual[3] == 1)
	{
    // 	afterX = getAfterX(-1,afterAngle);
	// 	afterY = getAfterY(-1,afterAngle);
		// score += 2;
		score++;
	}

	// // if(individual[4] == 1)
  	// // {
	// //   if(stadium->inObstacle(afterX, afterY, getRadius() && !stadium->inObstacle(getCenter()->getX(),getCenter()->getY() , getRadius() )))
	// //   {
	// // 	score += 30;
	// //   }else{
	// // 	score -=2;
	// //   }
  	// // 	score--;

	// // }
	
	double x,y;
	simulateLook(afterX,afterY, afterAngle, x,y);
	
	// if(!stadium->isValidMoveNPC(this,afterX,afterY))
	// {
	// 	score -= 999999;
	// }else

	// double norma = atan2(playerY, playerX ) - atan2(afterY, afterX) * getRadius() / current_distance;
	double norma = player->distance2D(afterX,afterY) / current_distance;
	 if(norma < 1)
	 {
		score += (1 - norma)*3;
	 }
  	// cout << afterX << ":"<<afterY<< ":"<< score<<endl;
    
	 score += ((double) rand() / (RAND_MAX)) + 1;
	return score;
}

void NPC::setCurrentMovement(vector<int> movement)
{
	current_movement = movement;
}

vector<int> NPC::getCurrentMovement(void)
{
	return current_movement;
}