#include "Rectangle.h"
#include <GL/gl.h>
#include <GL/glu.h>

Rectangle::Rectangle(double r,double g,double b){
    r_color = r;
    g_color = g;
    b_color = b;
    drawn = false;
}
Rectangle::Rectangle(double r,double g,double b,Point* tl,Point* bl,Point* tr,Point* br){
    r_color = r;
    g_color = g;
    b_color = b;
    topLeft = tl;
    bottomLeft = bl;
    topRight = tr;
    bottomRight = br;
    drawn = false;
}
void Rectangle::setTopLeft(Point* p){
    topLeft = p;
}
void Rectangle::setBottomLeft(Point* p){
    bottomLeft = p;
}
void Rectangle::setBottomRight(Point* p){
    bottomRight = p;
}
void Rectangle::setTopRight(Point* p){
    topRight = p;
}
double Rectangle::getRColor(void){
    return r_color;
}
double Rectangle::getGColor(void){
    return g_color;
}
double Rectangle::getBColor(void){
    return b_color;
}
void Rectangle::drawRectangle(void){
    glColor3f(r_color,g_color,b_color);
 
     glBegin(GL_QUADS);
          glVertex2f( topLeft->getX(), topLeft->getY());                        // Top Left
          glVertex2f( bottomLeft->getX(), bottomLeft->getY());               // Bottom Left
          glVertex2f( bottomRight->getX(), bottomRight->getY());               // Bottom Right
          glVertex2f( topRight->getX(), topRight->getY());                // Top Right
     glEnd();
}
void Rectangle::drawRectangle(double width,double height){
    glColor3f(r_color,g_color,b_color);
 
     glBegin(GL_QUADS);
          glVertex2f( -width/2.0, 0.0);                        // Top Left
          glVertex2f( -width/2.0, height);               // Bottom Left
          glVertex2f( width/2.0, height);               // Bottom Right
          glVertex2f( width/2.0, 0.0);                // Top Right
     glEnd();
}
bool Rectangle::isDrawn(void){
    return drawn;
}
