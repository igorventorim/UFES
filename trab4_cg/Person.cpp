#include "Person.h"
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
#define UPDATE_VELOCITY_PERSON moveVelocity*Stadium::MILLISECONDS_BY_FRAME
#define SCALE_PERSON 1

Person::Person(Circle* circle, double shot, double move)
{
    center = new Point(circle->getCoord_x(),circle->getCoord_y());
    head = circle;
    moveVelocity = move;
    shotVelocity = shot;
    bufferInverse = 0;
    personAngle = 0;
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


    look = new Point(0,0);
    adjustLook();
    

}

bool Person::isJumping(void)
{
    return jumping;
}
void Person::setJumping(bool jump)
{
    jumping = jump;
}

Circle* Person::getHead(void)
{
    return head;
}

void Person::draw(void)
{
    head->setCenter(center->getX(), center->getY());
    glPushMatrix();

            glTranslatef(center->getX(), center->getY(), 0);
            glRotatef(personAngle, 0,0,1);
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
double Person::getHeadRadius(void)
{
    return head->getRadius();
}

void Person::setHeadRadius(double r)
{
    return head->setRadius(r);
}

double Person::getRadius()
{
    return radius;
}

Shot* Person::atirar(void){

    adjustLook();
    // double x0=head->getRadius()+RADIUS_SHOULDER_A/2;
    // double y0=HEIGHT_HAND;
    // double x = x0 * cos(personAngle*M_PI/180) - y0 * sin(personAngle*M_PI/180) + center->getX();
    // double y = x0 * sin(personAngle*M_PI/180) + y0 * cos(personAngle*M_PI/180) + center->getY();
    // cout << "x:"<<x<<" y:"<<y<<" o:"<< personAngle<<"\n";
    Color* color = new Color(1.0,1.0,0);
    Circle* circle = new Circle(0,color,RADIUS_SHOT,look->getX(),look->getY());
    Shot* shot = new Shot(circle,shotVelocity,personAngle+angleHand+90);
    return shot;
}

void Person::rotateRight(void)
{
    if(down){
        incPersonAngle(UPDATE_VELOCITY_PERSON);
    }else{
        incPersonAngle(-UPDATE_VELOCITY_PERSON);
    }
    adjustLook();
    
}

bool Person::getDown(void)
{
    return down;
}

void Person::rotateLeft(void)
{

    if(down){
        incPersonAngle(-UPDATE_VELOCITY_PERSON);
    }else{
        incPersonAngle(UPDATE_VELOCITY_PERSON);
    }
    adjustLook();
}
void Person::moveUp(void)
{
    center->moveX(UPDATE_VELOCITY_PERSON*cos((personAngle+90)*M_PI/180));
    center->moveY(UPDATE_VELOCITY_PERSON*sin((personAngle+90)*M_PI/180));
    changeInverseFoots();
    adjustLook();
}
void Person::moveDown(void)
{
    center->moveX(-UPDATE_VELOCITY_PERSON*cos((personAngle+90)*M_PI/180));
    center->moveY(-UPDATE_VELOCITY_PERSON*sin((personAngle+90)*M_PI/180));
    changeInverseFoots();
    adjustLook();
}

double Person::getAfterX(int v, double personAngle)
{
    if(v > 0)
    {
        return UPDATE_VELOCITY_PERSON*cos((personAngle+90)*M_PI/180) + center->getX();
    }else
    {
        return -UPDATE_VELOCITY_PERSON*cos((personAngle+90)*M_PI/180) + center->getX();
    }
}
double Person::getAfterY(int v, double personAngle)
{
    if(v > 0)
    {
       return UPDATE_VELOCITY_PERSON*sin((personAngle+90)*M_PI/180) + center->getY();
    }else
    {
       return -UPDATE_VELOCITY_PERSON*sin((personAngle+90)*M_PI/180) + center->getY();
    }
}

double Person::getCoord_x(void)
{
    center->getX();
}
double Person::getCoord_y(void)
{
    center->getY();
}

void Person::setPersonAngle(double a){
    personAngle = a;
}
double Person::getPersonAngle(void){
    return personAngle;
}
void Person::incPersonAngle(double a){
    personAngle += a;
}

void Person::setOnElement(bool value)
{
    onElement = value;
}
bool Person::isOnElement(void)
{
    return onElement;
}

void Person::moveHand(double x,double y)
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

float Person::angleBetween(double x1, double y1, double x2, double y2)
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


void Person::changeInverseFoots(void)
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

void Person::jump(void)
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

void Person::inverse(void)
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

void Person::changeSize(void)
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

void Person::setDown(bool value)
{
    down = value;
}


bool Person::getResize()
{
    return resize;
}

Point* Person::getCenter()
{
    return center;
}

double Person::getScale(void)
{
    return scale;
}

double Person::getScaleInit(void)
{
    return scaleInit;
}

void Person::setHeightOnObstacle(double value)
{
    heightOnObstacle = value;
}

bool Person::isJumpingOnElement(void)
{
    return jumpingOnElement;
}

void Person::adjustLook(void)
{
    double x0=head->getRadius()+RADIUS_SHOULDER_A/2;
    double y0=HEIGHT_HAND;
    double x = x0 * cos(personAngle*M_PI/180) - y0 * sin(personAngle*M_PI/180) + center->getX();
    double y = x0 * sin(personAngle*M_PI/180) + y0 * cos(personAngle*M_PI/180) + center->getY();
    look->setPoint2D(x,y);
}

Point* Person::getLook(void)
{
    return look;
}

double Person::getUpdateVelocityPerson(void)
{
    return UPDATE_VELOCITY_PERSON;
}

double Person::getHeightHand(void)
{
    return HEIGHT_HAND;
}

double Person::getRadiusShoulderA(void)
{
    return RADIUS_SHOULDER_A;
}

bool Person::isMe(Person* p)
{
    if(getCoord_x() == p->getCoord_x() && getCoord_y() == p->getCoord_y())
    {
        return true;
    }else
    {
        return false;
    }
}

