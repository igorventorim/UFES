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
#define UPDATE_VELOCITY_PLAYER moveVelocity*Stadium::MILLISECONDS_BY_FRAME
#define UPDATE_VELOCITY_SHOT shotVelocity*Stadium::MILLISECONDS_BY_FRAME
#define SCALE_PERSON 1

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
    scaleInit = scale = SCALE_PERSON;


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
// void Player::setHead(Circle* circle)
// {
//     head = circle;
// }
// Circle* Player::getHead(void)
// {
//     return head;
// }
bool Player::isJumping(void)
{
    return jumping;
}
void Player::setJumping(bool jump)
{
    jumping = jump;
}
// void Player::setHand(Rectangle* r)
// {
//     hand = r;
// }
// void Player::setRFoot(Rectangle* r)
// {
//     rFoot = r;
// }
// void Player::setLFoot(Rectangle* r)
// {
//     lFoot = r;
// }
// Rectangle* Player::getHand(void)
// {
//     return hand;
// }
// Rectangle* Player::getLFoot(void)
// {
//     return lFoot;
// }
// Rectangle* Player::getRFoot(void)
// {
//     return rFoot;
// }
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

    double x0=head->getRadius()+RADIUS_SHOULDER_A/2;
    double y0=HEIGHT_HAND;
    double x = x0 * cos(playerAngle*M_PI/180) - y0 * sin(playerAngle*M_PI/180) + center->getX();
    double y = x0 * sin(playerAngle*M_PI/180) + y0 * cos(playerAngle*M_PI/180) + center->getY();
    // cout << "x:"<<x<<" y:"<<y<<" o:"<< playerAngle<<"\n";
    Color* color = new Color(1.0,1.0,0);
    Circle* circle = new Circle(0,color,RADIUS_SHOT,x,y);
    Shot* shot = new Shot(circle,UPDATE_VELOCITY_SHOT,playerAngle+angleHand+90);
    return shot;
}

void Player::rotateRight(void)
{
    if(down){
        incPlayerAngle(UPDATE_VELOCITY_PLAYER);
    }else{
        incPlayerAngle(-UPDATE_VELOCITY_PLAYER);
    }
    
}
void Player::rotateLeft(void)
{

    if(down){
        incPlayerAngle(-UPDATE_VELOCITY_PLAYER);
    }else{
        incPlayerAngle(UPDATE_VELOCITY_PLAYER);
    }
}
void Player::moveUp(void)
{
    center->moveX(UPDATE_VELOCITY_PLAYER*cos((playerAngle+90)*M_PI/180));
    center->moveY(UPDATE_VELOCITY_PLAYER*sin((playerAngle+90)*M_PI/180));
    changeInverseFoots();
}
void Player::moveDown(void)
{
    center->moveX(-UPDATE_VELOCITY_PLAYER*cos((playerAngle+90)*M_PI/180));
    center->moveY(-UPDATE_VELOCITY_PLAYER*sin((playerAngle+90)*M_PI/180));
    changeInverseFoots();
}

double Player::getAfterX(int v)
{
    if(v > 0)
    {
        return UPDATE_VELOCITY_PLAYER*cos((playerAngle+90)*M_PI/180) + center->getX();
    }else
    {
        return -UPDATE_VELOCITY_PLAYER*cos((playerAngle+90)*M_PI/180) + center->getX();
    }
}
double Player::getAfterY(int v)
{
    if(v > 0)
    {
       return UPDATE_VELOCITY_PLAYER*sin((playerAngle+90)*M_PI/180) + center->getY();
    }else
    {
       return -UPDATE_VELOCITY_PLAYER*sin((playerAngle+90)*M_PI/180) + center->getY();
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
// void Player::setLShoulder(Elipse* e)
// {
//     lShoulder = e;
// }
// void Player::setRShoulder(Elipse* e){
//     rShoulder = e;
// }
// Elipse* Player::getLShoulder(void){
//     return lShoulder;
// }
// Elipse* Player::getRShoulder(void){
//     return rShoulder;
// }

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
    double newX =  center->getX() - x;
    double newY =  center->getY() - y;
    angleHand = atan2(newX - hand->getCoord_x(),newY - hand->getCoord_y() + HEIGHT_HAND) *180/M_PI - 45;
    // angleHand = angleBetween(newX,newY,hand->getCoord_x(),hand->getCoord_y()) *180/M_PI - 45;
    if(angleHand > 45)
    {
        angleHand = 45;
    }else if(angleHand < -45)
    {
        angleHand = -45;
    }
}

float Player::angleBetween(double x1, double y1, double x2, double y2)
{
    float len1 = sqrt(x1 * x1 + y1 * y1);
    float len2 = sqrt(x2 * x2 + y2 * y2);

    float dot = x1 * x2 + y1 * y2;

    float a = dot / (len1 * len2);

    if (a >= 1.0)
        return 0.0;
    else if (a <= -1.0)
        return M_PI;
    else
        return acos(a); // 0..PI
}


void Player::changeInverseFoots(void)
{
    inverseFoots = !inverseFoots;
    count++;
    if(count < 3){ return;}
    count=0;
    lFoot->setCoord_y(sin(bufferInverse*M_PI/180)* -lFoot->getHeight());
    rFoot->setCoord_y(cos(bufferInverse*M_PI/180)* -rFoot->getHeight());

    bufferInverse += 15 * signal;
    if(bufferInverse >= 90 && signal > 0 ){ signal = -1; }
    else if(bufferInverse <= 0 && signal < 0){ signal = 1;}
}

void Player::jump(void)
{   
    if(!jumping)
    {
        scaleInit = scale;
        jumping = true;
        startJump = std::chrono::system_clock::now();
        inverse();
       
    }else if(onElement && !jumpingOnElement)
    {
        jumpingOnElement = true;
        scaleInit = scale;
        startJump = std::chrono::system_clock::now();
        inverse();
    }
}

void Player::inverse(void)
{
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
    if(resize && !jumpingOnElement)
    {
        elapsed += 1 + (1 - heightOnObstacle) ;
    }
    if(elapsed <= 1)
    {
        scale = (scaleInit + elapsed*(scaleInit/2));
    }else{
        if(!jumpingOnElement && onElement && (scale-1) <= heightOnObstacle*(scaleInit/2) + (scaleInit/2)*0.02 )
        {
         startJump =  std::chrono::system_clock::now(); 
         resize = true; 
         return;
        }
        
        scale = scaleInit + (scaleInit/2) - (elapsed*(scaleInit/2) - (scaleInit/2));
        if(elapsed >= 2)
        {
            if(jumpingOnElement)
            {
                jumpingOnElement = false;
                startJump =  std::chrono::system_clock::now();
                resize = true;
            }else
            {
                resize = false;
                jumping = false;
            }
            scale = scaleInit;
            scaleInit = SCALE_PERSON;
        }
    }

}

void Player::setDown(bool value)
{
    down = value;
}


bool Player::getResize()
{
    return resize;
}

Point* Player::getCenter()
{
    return center;
}

double Player::getScale(void)
{
    return scale;
}

double Player::getScaleInit(void)
{
    return scaleInit;
}

void Player::setHeightOnObstacle(double value)
{
    heightOnObstacle = value;
}

bool Player::isJumpingOnElement(void)
{
    return jumpingOnElement;
}