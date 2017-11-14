#include "NPC.h"
#include <iostream>
#include <cmath>
#include "Stadium.h"


NPC::NPC(Circle* circle, double shot, double move): Person(circle,shot,move){}

bool NPC::isMe(Person* p)
{
    if(getCoord_x() == p->getCoord_x() && getCoord_y() == p->getCoord_y())
    {
        return true;
    }else
    {
        return false;
    }
}

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
void NPC::moveNPC(vector<int> individual,int size_vector)
{

	double value = movementEvaluate(individual,size_vector);
	
	if(value < 0){return;}	
  	if(individual[0])
	{
		rotateRight();
	}

	if(individual[1])
	{
		rotateLeft();
	}

	if(individual[2])
	{
		moveUp();
	}

	if(individual[3])
	{
		moveDown();
	}

	if(individual[4])
	{
		jump();
	}

}


/*
	POSITION 0: ROTATE RIGHT
	POSITION 1: ROTATE LEFT
	POSITION 2: MOVE UP
	POSITION 3: MOVE DOWN
	POSITION 4: JUMP
*/
int NPC::movementEvaluate(vector<int> individual,int size_vector)
{
  	bool walk = false;
	int score = 0;
	double afterAngle = 0;
	double current_distance = getLook()->distance2D(player->getX(),player->getY());
	double afterX = getCenter()->getX();
	double afterY = getCenter()->getY();

	if(individual[0] == 1)
	{
		afterAngle = getAfterPersonAngle(1,0);
		score++;
		
	}
	if(individual[1] == 1)
	{
		afterAngle = getAfterPersonAngle(0,1);
		score++;
	}
	
	if(individual[2] == 1)
	{
    	afterX = getAfterX(1,afterAngle);
    	afterY = getAfterY(1,afterAngle);
		score =+ 3;
		walk = true;
	}

	if(individual[3] == 1)
	{
    	afterX = getAfterX(-1,afterAngle);
		afterY = getAfterY(-1,afterAngle);
		score =+ 2;
		walk = true;
	}

	if(individual[4] == 1)
  	{
	  if(stadium->inObstacle(afterX, afterY, getRadius() && !stadium->inObstacle(getCenter()->getX(),getCenter()->getY() , getRadius() )))
	  {
		score += 30;
		// moveOk = true;
	  }else{
		score -=2;
	  }
	}
	
	double x,y;
	simulateLook(afterX,afterY, afterAngle, x,y);

	if(!stadium->isValidMoveNPC(this,afterX,afterY) )
	{
		score -= 999999;
	}else if(player->distance2D(x,y) < current_distance)
	{
		score += 10;
	}
  


// 	if(individual[0])
// 	{
// 		afterAngle = getAfterPersonAngle(1,0);
//     	rotate = true;
//     	score++;
// 	}

// 	if(individual[1])
// 	{
//     	afterAngle = getAfterPersonAngle(0,1);
// 		if(rotate){
// 		 score = -99;
// 		}
//     	score++;
// 	}

// 	if(individual[2])
// 	{
//     	afterX = getAfterX(1,afterAngle);
//     	afterY = getAfterY(1,afterAngle);
//     	walk = true;
//     	score += 4;
// 	}

// 	if(individual[3])
// 	{
//     	afterX = getAfterX(-1,afterAngle);
//     	afterY = getAfterY(-1,afterAngle);
// 		if(walk)
// 		{
// 		score = -99;
// 		}
//     	walk = true;
//     	score +=2;
// 	}

//   if(walk)
//   {
//     if(individual[4])
//   	{
//       score +=2;
//   	}
//   }else{
//     if(individual[4])
//   	{
//       score = -99;
//   	}
//   }
//   double x,y;
//   simulateLook(afterX,afterY, afterAngle, x,y);

//   if(!stadium->isValidMoveNPC(this,afterX,afterY))
//   {
// 	score -= 999999;
//   }else if(player->distance2D(x,y) < current_distance)
//   {
//      score += 10;
//   }
    
 
	return score;
}


void NPC::setStadium(Stadium* s)
{
	stadium = s;
}