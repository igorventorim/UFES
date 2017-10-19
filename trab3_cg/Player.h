#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Circle.h"
#include "Rectangle.h"
class Player
{
	private:
		Circle *head;
		Rectangle *lHand,*rHand,*lFoot,*rFoot;
		double moveVelocity, shotVelocity;
		bool jumping;

	public:
		Player(Circle*,double,double);
		void setHead(Circle*);
		Circle* getHead(void);
		bool isJumping(void);
		void setJumping(bool);
		void setLHand(Rectangle*);
		void setRHand(Rectangle*);
		void setRFoot(Rectangle*);
		void setLFoot(Rectangle*);
		Rectangle* getLHand(void);
		Rectangle* getLFoot(void);
		Rectangle* getRHand(void);
		Rectangle* getRFoot(void);
		void draw(void);
		double getHeadRadius(void);
		void setHeadRadius(double);
		void girar(void);
		void atirar(void);
		void moveRight(void);
		void moveLeft(void);
		void moveUp(void);
		void moveDown(void);
		double getCoord_x(void);
		double getCoord_y(void);


};
#endif