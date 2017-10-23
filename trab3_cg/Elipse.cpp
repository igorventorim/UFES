#include "Elipse.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>
#define DEG2RAD 3.14159/180.0
using namespace std;
Elipse::Elipse(double a,double b){
    radiusA = a;
    radiusB = b;
    drawn = false;
}
Elipse::Elipse(double ra,double rb,Point* p,Color *c){
    radiusA = ra;
    radiusB = rb;
    center = p;
    color = c;
    drawn = false;
}

void Elipse::setColor(Color* c)
{
    color = c;
}
Color* Elipse::getColor(void)
{
    return color;
}

void Elipse::setCenter(Point* p){
    center = p;
}
Point* Elipse::getCenter(void){
    return center;
}
bool Elipse::isDrawn(void){
    return drawn;
}

double Elipse::getCoord_x(void)
{
    return center->getX();
}

double Elipse::getCoord_y(void)
{
    return center->getY();
}

void Elipse::setCoord_x(double x)
{
    center->setX(x);
}

void Elipse::setCoord_y(double y)
{
    center->setY(y);
}

void Elipse::drawElipse(void){


    glColor3f(color->getRColor(),color->getGColor(),color->getBColor());
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    
    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * M_PI;
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0); // center of circle
        for(i = 0; i <= triangleAmount;i++) { 
            glVertex2f(radiusA * cos(i *  twicePi / triangleAmount), radiusB * sin(i * twicePi / triangleAmount));
        }
    glEnd();
    drawn = true;
}

