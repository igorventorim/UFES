#include "NPC.h"
#include <iostream>
#include <cmath>

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
	// cout << "Vou mover para : [ ";
	// for(int j = 0; j < size_vector; j++)
  //   {
  //       cout << individual[j] << " ";
  //   }
  //   cout << "]"<<endl;

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
  bool rotate = false;
  bool walk = false;
	int score = 0;
	double afterAngle = getAfterPersonAngle(0,0);
	double current_distance = getLook()->distance2D(player->getX(),player->getY());
	double afterX = getCenter()->getX();
	double afterY = getCenter()->getY();

	if(individual[0])
	{
		afterAngle = getAfterPersonAngle(1,0);
    rotate = true;
    score++;
	}

	if(individual[1])
	{
    afterAngle = getAfterPersonAngle(0,1);
    if(rotate){
      score = -2;
    }
    score++;
	}

	if(individual[2])
	{
    afterX = getAfterX(1,afterAngle);
    afterY = getAfterY(1,afterAngle);
    walk = true;
    score++;
	}

	if(individual[3])
	{
    afterX = getAfterX(-1,afterAngle);
    afterY = getAfterY(-1,afterAngle);
    if(walk)
    {
      score = -2;
    }
    walk = true;
    score++;
	}

  if(walk)
  {
    if(individual[4])
  	{
      score++;
  	}
  }else{
    if(individual[4])
  	{
      score--;
  	}
  }
  double x,y;
  simulateLook(afterX,afterY, afterAngle, x,y);

   if(player->distance2D(x,y))
   {
     score += 5;
   }



	return score;
}
