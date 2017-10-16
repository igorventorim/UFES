#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Circle.h"
#include "Rectangle.h"
class Player
{
	private:
		Circle *head;
		Rectangle *lHand,*rHand,*lFoot,*rFoot;
		bool jumping;

	public:
		// Player();
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

		// void girar()
		// void atirar()


};
#endif