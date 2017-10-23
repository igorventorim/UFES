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
void Elipse::drawElipse(void){
    cout << "Entreiii" << "\n";
    glPushMatrix();
        glTranslatef(center->getX(), center->getY(), 0);
        glColor3f(r_color,g_color,b_color);
        int i;
        glBegin(GL_LINE_LOOP);
        
        for(i=0;i<360;i++)
        {
            float rad = i*DEG2RAD;
            glVertex2f(cos(rad)*radiusA, sin(rad)*radiusB);
        }
        
        glEnd();
    glPopMatrix();
    drawn = true;
}

