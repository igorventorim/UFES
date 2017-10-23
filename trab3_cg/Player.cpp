#include "Player.h"
#include "Circle.h"
#include <GL/gl.h>
#include <GL/glu.h>
#define RADIUS_SHOULDER_A 13
#define RADIUS_SHOULDER_B 3
#define WIDTH_FOOT 5
#define HEIGHT_LEFT 20

Player::Player(Circle* circle, double shot, double move)
{
    center = new Point(circle->getCoord_x(),circle->getCoord_y());
    head = circle;
    moveVelocity = move;
    shotVelocity = shot;

    // CREATE SHOULDERS
    Point *lPoint = new Point(-circle->getRadius(),0);
    Point *rPoint = new Point(circle->getRadius(),0);
    lShoulder = new Elipse(RADIUS_SHOULDER_A,RADIUS_SHOULDER_B,lPoint,circle->getRColor(),circle->getGColor(),circle->getBColor());
    rShoulder = new Elipse(RADIUS_SHOULDER_A,RADIUS_SHOULDER_B,rPoint,circle->getRColor(),circle->getGColor(),circle->getBColor());

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
// void Player::setRHand(Rectangle* r)
// {
//     rHand = r;
// }
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
// Rectangle* Player::getRHand(void)
// {
//     return rHand;
// }
Rectangle* Player::getRFoot(void)
{
    return rFoot;
}
void Player::draw(void)
{
    glPushMatrix();
			glTranslatef(head->getCoord_x(), head->getCoord_y(), 0);
            head->drawCircle();
            lShoulder->drawElipse();
            rShoulder->drawElipse();

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
void Player::girar(void){}
void Player::atirar(void){}

void Player::moveRight(void)
{
    head->moveX(moveVelocity);
}
void Player::moveLeft(void)
{
    head->moveX(-moveVelocity);
}
void Player::moveUp(void)
{
    head->moveY(moveVelocity);
}
void Player::moveDown(void)
{
    head->moveY(-moveVelocity);
}
double Player::getCoord_x(void)
{
    head->getCoord_x();
}
double Player::getCoord_y(void)
{
    head->getCoord_y();
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