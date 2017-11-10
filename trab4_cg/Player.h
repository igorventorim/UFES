#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Circle.h"
#include "Rectangle.h"
#include "Elipse.h"
#include "Point.h"
#include "Shot.h"
#include <chrono>
#include <ctime>


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
		double angleHand;
		int bufferInverse;
		int count = 0;
		int signal = 1;
	    std::chrono::time_point<std::chrono::system_clock> startJump;
		double scale;
		double scaleInit;
		bool onElement;
		bool down;
		bool resize;
		bool jumpingOnElement;
		double heightOnObstacle;

	public:
		Player(Circle*,double,double);
		bool isJumping(void);
		void setJumping(bool);
		void draw(void);
		double getHeadRadius(void);
		void setHeadRadius(double);
		Shot* atirar(void);
		void rotateRight(void);
		void rotateLeft(void);
		void moveUp(void);
		void moveDown(void);
		double getCoord_x(void);
		double getCoord_y(void);
		void setPlayerAngle(double);
		double getPlayerAngle(void);
		void incPlayerAngle(double);
		void changeInverseFoots(void);
		void moveHand(double,double);
		double getRadius(void);
		double getAfterX(int);
		double getAfterY(int);
		void jump(void);
		void changeSize(void);
		void setOnElement(bool);
		bool isOnElement(void);
		float angleBetween(double, double, double, double);
		void setDown(bool value);
		bool getResize(void);
		Point* getCenter(void);
		double getScale(void);
		double getScaleInit(void);
		void setHeightOnObstacle(double);
		bool isJumpingOnElement(void);
		void inverse(void);

};
#endif