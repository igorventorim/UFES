#include "Player.h"
#include "Circle.h"
#include "Stadium.h"
#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#define RADIUS_SHOULDER_A head->getRadius()*0.8
#define RADIUS_SHOULDER_B head->getRadius()*0.4
#define WIDTH_FOOT head->getRadius()*0.7
#define HEIGHT_FOOT head->getRadius()*1.9
#define WIDTH_HAND head->getRadius()*0.5
#define HEIGHT_HAND head->getRadius()*1.9
#define RADIUS_SHOT head->getRadius()*0.1

Player::Player(Circle* circle, double shot, double move)
{
    center = new Point(circle->getCoord_x(),circle->getCoord_y());
    head = circle;
    moveVelocity = move;
    shotVelocity = shot;
    bufferInverse = 0;
    playerAngle = 0;
    angleHand = 0;
    inverseFoots = false;
    onElement = false;
    radius = HEIGHT_FOOT;
    scale = 1;


    // CREATE SHOULDERS
    Point *lShoulderPoint = new Point(-circle->getRadius(),0);
    Point *rShoulderPoint = new Point(circle->getRadius(),0);
    lShoulder = new Elipse(RADIUS_SHOULDER_A,RADIUS_SHOULDER_B,lShoulderPoint,head->getColor());
    rShoulder = new Elipse(RADIUS_SHOULDER_A,RADIUS_SHOULDER_B,rShoulderPoint,head->getColor());

    // CREATE FOOTS
    Color *footColor = new Color(0.0,0.0,0.0);
    Point *lFootPoint = new Point(-circle->getRadius()/2,0);
    Point *rFootPoint = new Point(circle->getRadius()/2,-HEIGHT_FOOT);
    lFoot = new Rectangle(lFootPoint,WIDTH_FOOT,HEIGHT_FOOT,footColor);
    rFoot = new Rectangle(rFootPoint,WIDTH_FOOT,HEIGHT_FOOT,footColor);

    // CREATE HAND
    Point *handPoint = new Point(circle->getRadius()+RADIUS_SHOULDER_A/2,0);
    hand = new Rectangle(handPoint,WIDTH_HAND,HEIGHT_HAND,head->getColor());

}
void Player::setHead(Circle* circle)
{
    head = circle;
}
Circle* Player::getHead(void)
{
    return head;
}
bool Player::isJumping(void)
{
    return jumping;
}
void Player::setJumping(bool jump)
{
    jumping = jump;
}
void Player::setHand(Rectangle* r)
{
    hand = r;
}
void Player::setRFoot(Rectangle* r)
{
    rFoot = r;
}
void Player::setLFoot(Rectangle* r)
{
    lFoot = r;
}
Rectangle* Player::getHand(void)
{
    return hand;
}
Rectangle* Player::getLFoot(void)
{
    return lFoot;
}
Rectangle* Player::getRFoot(void)
{
    return rFoot;
}
void Player::draw(void)
{
    glPushMatrix();

            glTranslatef(center->getX(), center->getY(), 0);
            glRotatef(playerAngle, 0,0,1);
            glScalef(scale,scale,0);
            
            glPushMatrix();
                glTranslatef(lShoulder->getCoord_x(), lShoulder->getCoord_y(), 0);
                lShoulder->drawElipse();
            glPopMatrix();
      
            glPushMatrix();
                glTranslatef(rShoulder->getCoord_x(), rShoulder->getCoord_y(), 0);
                rShoulder->drawElipse();
            glPopMatrix();
                             
            glPushMatrix();
                glTranslatef(lFoot->getCoord_x(), lFoot->getCoord_y(), 0);
                rFoot->drawRectangle();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(rFoot->getCoord_x(), rFoot->getCoord_y(), 0);
                rFoot->drawRectangle();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(hand->getCoord_x(), hand->getCoord_y(), 0);
                glRotatef(angleHand,0,0,1);                
                hand->drawRectangle();
            glPopMatrix();
           
            head->drawCircle();

    glPopMatrix();
}
double Player::getHeadRadius(void)
{
    return head->getRadius();
}

void Player::setHeadRadius(double r)
{
    return head->setRadius(r);
}

double Player::getRadius()
{
    return radius;
}

Shot* Player::atirar(void){
    double x = center->getX()+head->getRadius()+RADIUS_SHOULDER_A ;//* cos(playerAngle*M_PI/180) + center->getY()+HEIGHT_HAND * sin(playerAngle*M_PI/180);
    double y = /*-center->getX()+head->getRadius()+RADIUS_SHOULDER_A * sin(playerAngle*M_PI/180) + */center->getY()+HEIGHT_HAND;// * cos(playerAngle*M_PI/180);;
    Color* color = new Color(1.0,1.0,0);
    Circle* circle = new Circle(0,color,RADIUS_SHOT,x,y);
    Shot* shot = new Shot(circle,shotVelocity,angleHand);
    return shot;
    // return NULL;
}

void Player::rotateRight(void)
{
    // head->moveX(moveVelocity);
    incPlayerAngle(-moveVelocity);
}
void Player::rotateLeft(void)
{
    // head->moveX(-moveVelocity);
    incPlayerAngle(moveVelocity);
}
void Player::moveUp(void)
{
    center->moveX(moveVelocity*cos((playerAngle+90)*M_PI/180));
    center->moveY(moveVelocity*sin((playerAngle+90)*M_PI/180));
}
void Player::moveDown(void)
{
    center->moveX(-moveVelocity*cos((playerAngle+90)*M_PI/180));
    center->moveY(-moveVelocity*sin((playerAngle+90)*M_PI/180));
}

double Player::getAfterX(int v)
{
    if(v > 0)
    {
        return moveVelocity*cos((playerAngle+90)*M_PI/180) + center->getX();
    }else
    {
        return -moveVelocity*cos((playerAngle+90)*M_PI/180) + center->getX();   
    }
}
double Player::getAfterY(int v)
{
    if(v > 0)
    {
       return moveVelocity*sin((playerAngle+90)*M_PI/180) + center->getY();
    }else
    {
       return -moveVelocity*sin((playerAngle+90)*M_PI/180) + center->getY();
    }
}

double Player::getCoord_x(void)
{
    center->getX();
}
double Player::getCoord_y(void)
{
    center->getY();
}
void Player::setLShoulder(Elipse* e)
{
    lShoulder = e;
}
void Player::setRShoulder(Elipse* e){
    rShoulder = e;
}
Elipse* Player::getLShoulder(void){
    return lShoulder;
}
Elipse* Player::getRShoulder(void){
    return rShoulder;
}

void Player::setPlayerAngle(double a){
    playerAngle = a;
}
double Player::getPlayerAngle(void){
    return playerAngle;
}
void Player::incPlayerAngle(double a){
    playerAngle += a;
}

void Player::setOnElement(bool value)
{
    onElement = value;
}
bool Player::isOnElement(void)
{
    return onElement;
}

void Player::moveHand(double x,double y)
{
    double newX =  center->getX() - x ;
    double newY =  center->getY() - y;
    angleHand = atan2(newX - hand->getCoord_y(),newY - hand->getCoord_x()) *180/M_PI - 45; 
    if(angleHand > 45)
    {
        angleHand = 45;
    }else if(angleHand < -45)
    {
        angleHand = -45;
    }
}


void Player::changeInverseFoots(void)
{
    inverseFoots = !inverseFoots;
    bufferInverse++;
    if(bufferInverse < 5 ){ return;}
    bufferInverse = 0;
    if(inverseFoots)
    {
        lFoot->setCoord_y(-lFoot->getHeight());
        rFoot->setCoord_y(0);
    }else
    {
        lFoot->setCoord_y(0);
        rFoot->setCoord_y(-rFoot->getHeight());
    }

}

void Player::jump(void)
{
    jumping = true;
    startJump = std::chrono::system_clock::now();
    inverseFoots = !inverseFoots;
    if(inverseFoots)
    {
        lFoot->setCoord_y(-lFoot->getHeight());
        rFoot->setCoord_y(0);
    }else
    {
        lFoot->setCoord_y(0);
        rFoot->setCoord_y(-rFoot->getHeight());
    }

}

void Player::changeSize(void)
{
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds> ( std::chrono::system_clock::now() - startJump).count()/1000.00;
    if(elapsed < 1)
    {
        scale = (1.0 + elapsed*0.5);
    }else{
        if(onElement){ return;}
        scale = 1.0 + 0.5 - (elapsed*0.5 -0.5);
        if(elapsed >= 2)
        {
            jumping = false;
            scale = 1.0;
        }
    }

}