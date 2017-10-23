#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Circle.h"
#include "Rectangle.h"
#include "Elipse.h"
#include "Point.h"
class Player
{
	private:
		Point *center;
		double radius;
		Circle *head;
		Rectangle *hand,*lFoot,*rFoot;
		Elipse *lShoulder,*rShoulder;
		double moveVelocity, shotVelocity;
		bool jumping,inverseFoots;
		double playerAngle;

	public:
		Player(Circle*,double,double);
		void setHead(Circle*);
		Circle* getHead(void);
		bool isJumping(void);
		void setJumping(bool);
		// void setLHand(Rectangle*);
		// void setRHand(Rectangle*);
		void setHand(Rectangle*);
		void setRFoot(Rectangle*);
		void setLFoot(Rectangle*);
		void setLShoulder(Elipse*);
		void setRShoulder(Elipse*);
		Elipse* getLShoulder(void);
		Elipse* getRShoulder(void);
		Rectangle* getHand(void);
		Rectangle* getLFoot(void);
		// Rectangle* getRHand(void);
		Rectangle* getRFoot(void);
		void draw(void);
		double getHeadRadius(void);
		void setHeadRadius(double);
		void girar(void);
		void atirar(void);
		void rotateRight(void);
		void rotateLeft(void);
		void moveUp(void);
		void moveDown(void);
		double getCoord_x(void);
		double getCoord_y(void);
		void setPlayerAngle(double);
		double getPlayerAngle(void);
		void incPlayerAngle(double);
		void changeInverseFoots();


};
#endif