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
Elipse::Elipse(double ra,double rb,Point* c,double r,double g,double b){
    radiusA = ra;
    radiusB = rb;
    center = c;
    r_color = r;
    g_color = g;
    b_color = b;
    drawn = false;
}
double Elipse::getRColor(void){
    return r_color;
}
double Elipse::getGColor(void){
    return g_color;
}
double Elipse::getBColor(void){
    return b_color;
}
void Elipse::setRColor(double color){
    r_color = color;
}
void Elipse::setGColor(double color){
    g_color = color;
}
void Elipse::setBColor(double color){
    b_color = color;
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


    glColor3f(r_color,g_color,b_color);
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

