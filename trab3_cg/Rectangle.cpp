#include "Rectangle.h"
#include <GL/gl.h>
#include <GL/glu.h>


Rectangle::Rectangle(Color *c,double w,double h){
    color = c;
    width = w;
    height = h;
    drawn = false;
}
Rectangle::Rectangle(Color *c,Point* tl,Point* bl,Point* tr,Point* br){
    color = c;
    topLeft = tl;
    bottomLeft = bl;
    topRight = tr;
    bottomRight = br;
    drawn = false;
}

Rectangle::Rectangle(Point* o,double w,double h,Color*c)
{
  origin = o;
  width = w;
  height = h;
  color = c;
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

double Rectangle::getCoord_x(void)
{
  return origin->getX();
}
double Rectangle::getCoord_y(void)
{
  return origin->getY();
}
void Rectangle::setCoord_x(double x)
{
  origin->setX(x);
}
void Rectangle::setCoord_y(double y)
{
  origin->setY(y);
}

// void Rectangle::drawRectangle(void){
//     glColor3f(r_color,g_color,b_color);
 
//      glBegin(GL_QUADS);
//           glVertex2f( topLeft->getX(), topLeft->getY());                        // Top Left
//           glVertex2f( bottomLeft->getX(), bottomLeft->getY());               // Bottom Left
//           glVertex2f( bottomRight->getX(), bottomRight->getY());               // Bottom Right
//           glVertex2f( topRight->getX(), topRight->getY());                // Top Right
//      glEnd();
// }
void Rectangle::drawRectangle(){
    
    glColor3f(color->getRColor(),color->getGColor(),color->getBColor());
     glBegin(GL_QUADS);
          glVertex2f( -width/2.0, 0.0);                // Top Left
          glVertex2f( -width/2.0, height);             // Bottom Left
          glVertex2f( width/2.0, height);              // Bottom Right
          glVertex2f( width/2.0, 0.0);                 // Top Right
     glEnd();
     drawn = true;
}
bool Rectangle::isDrawn(void){
    return drawn;
}
