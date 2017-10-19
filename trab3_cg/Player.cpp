#include "Player.h"
#include "Circle.h"
#include <GL/gl.h>
#include <GL/glu.h>

Player::Player(Circle* circle, double shot, double move)
{
    head = circle;
    moveVelocity = move;
    shotVelocity = shot;
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
void Player::setLHand(Rectangle* r)
{
    lHand = r;
}
void Player::setRHand(Rectangle* r)
{
    rHand = r;
}
void Player::setRFoot(Rectangle* r)
{
    rFoot = r;
}
void Player::setLFoot(Rectangle* r)
{
    lFoot = r;
}
Rectangle* Player::getLHand(void)
{
    return lHand;
}
Rectangle* Player::getLFoot(void)
{
    return lFoot;
}
Rectangle* Player::getRHand(void)
{
    return rHand;
}
Rectangle* Player::getRFoot(void)
{
    return rFoot;
}
void Player::draw(void)
{
    glPushMatrix();
			glTranslatef(head->getCoord_x(), head->getCoord_y(), 0);
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