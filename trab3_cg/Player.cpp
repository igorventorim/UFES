#include "Player.h"
#include "Circle.h"
#include <GL/gl.h>
#include <GL/glu.h>
#define RADIUS_SHOULDER_A 16
#define RADIUS_SHOULDER_B 8
#define WIDTH_FOOT 14
#define HEIGHT_FOOT 38
#define WIDTH_HAND 10
#define HEIGHT_HAND 38

Player::Player(Circle* circle, double shot, double move)
{

    /* TODO: ADD PROPORTION */

    center = new Point(circle->getCoord_x(),circle->getCoord_y());
    head = circle;
    moveVelocity = move;
    shotVelocity = shot;

    // CREATE SHOULDERS
    Point *lShoulderPoint = new Point(-circle->getRadius(),0);
    Point *rShoulderPoint = new Point(circle->getRadius(),0);
    lShoulder = new Elipse(RADIUS_SHOULDER_A,RADIUS_SHOULDER_B,lShoulderPoint,circle->getRColor(),circle->getGColor(),circle->getBColor());
    rShoulder = new Elipse(RADIUS_SHOULDER_A,RADIUS_SHOULDER_B,rShoulderPoint,circle->getRColor(),circle->getGColor(),circle->getBColor());

    // CREATE FOOTS
    Color *footColor = new Color(0.0,0.0,0.0);
    Point *lFootPoint = new Point(-circle->getRadius()/2,0);
    Point *rFootPoint = new Point(circle->getRadius()/2,-HEIGHT_FOOT);
    lFoot = new Rectangle(lFootPoint,WIDTH_FOOT,HEIGHT_FOOT,footColor);
    rFoot = new Rectangle(rFootPoint,WIDTH_FOOT,HEIGHT_FOOT,footColor);

    // CREATE HAND
    Color *personColor = new Color(circle->getRColor(),circle->getGColor(),circle->getBColor());
    Point *handPoint = new Point(circle->getRadius()+RADIUS_SHOULDER_A/2,0);
    hand = new Rectangle(handPoint,WIDTH_HAND,HEIGHT_HAND,personColor);

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

            glTranslatef(head->getCoord_x(), head->getCoord_y(), 0);

            glPushMatrix();
                glTranslatef(hand->getCoord_x(), hand->getCoord_y(), 0);
                hand->drawRectangle();
            glPopMatrix();

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