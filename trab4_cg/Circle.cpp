#include "Circle.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include "Point.h"

using namespace std;

Circle::Circle(int identificador, Color* cor, double raio)
{
    id = identificador;
    color = cor;
    radius = radius;
    drawn = false;
    center = Point();
}

Circle::Circle(int identificador, Color* cor, double raio, double dX, double dY)
{
    id = identificador;
    color = cor;
    radius = raio;
    drawn = false;
    center = Point(dX,dY);
}

Circle::Circle(int identificador,double raio ,Color *c)
{
    id = identificador;
    radius = raio;
    color = c;
    drawn = false;
}

void Circle::setRadius(double r)
{
    radius = r;
}

void Circle::setColor(Color* c)
{
    color = c;
}

void Circle::setCoord_x(double x)
{
    center.setX(x);
}

void Circle::setCoord_y(double y)
{
    center.setY(y);
}

void Circle::moveX(double x)
{
    center.setX(x+center.getX());
}

void Circle::moveY(double y)
{
    center.setY(center.getY()-y);
}

void Circle::setCenter(double x,double y)
{
    center.setPoint2D(x,y);
}

double Circle::getRadius()
{
    return radius;
}

double Circle::getCoord_x()
{
    return center.getX();
}

double Circle::getCoord_y()
{
    return center.getY();
}

Color* Circle::getColor()
{
    return color;
}

// double Circle::getRColor(void)
// {
//     return r_color;
// }

// double Circle::getGColor(void)
// {
//     return g_color;
// }

// double Circle::getBColor(void)
// {
//     return b_color;
// }

bool Circle::isDrawn(void)
{
  return drawn;
}

void Circle::setDrawn(bool draw)
{
  drawn = draw;
}

void Circle::drawCircle(void)
{
  // float x2,y2;
  // float angle;
  //
  // glColor3f(getRColor(),getGColor(),getBColor());
  //
  // glBegin(GL_TRIANGLE_FAN);
  // glVertex2f(0,0);
  //
  // for (angle=0.0f;angle<360.0f;angle+=0.1)
  // {
  //     x2 = sin(angle)*getRadius();
  //     y2 = cos(angle)*getRadius();
  //     glVertex2f(x2,y2);
  // }
  // glEnd();

  int i;
  int triangleAmount = 700;
  GLfloat twicePi = 2.0f * M_PI;

  glEnable(GL_LINE_SMOOTH);
  glLineWidth(5.0);

  glBegin(GL_LINES);
      glColor3f(color->getRColor(),color->getGColor(),color->getBColor());
      for(i = 0; i <= triangleAmount; i++)
      {
          glVertex2f(0, 0);
          glVertex2f((getRadius() * cos(i * twicePi / triangleAmount)), (getRadius() * sin(i * twicePi / triangleAmount)));
      }
  glEnd();
}


double Circle::distance2Center(double x,double y)
{
    // return sqrt(pow(coord_x-x,2)+pow(coord_y-y,2));
    return center.distance2D(x,y);
}

bool Circle::pointInCircle(double x, double y)
{
    return distance2Center(x,y) < getRadius();
}

bool Circle::circleInCircle(double x, double y, double r)
{
    return distance2Center(x,y) < getRadius()+r;
}

void Circle::setUpdate(bool status)
{
    update = status;
}

bool Circle::getUpdate(void)
{
    return update;
}

int Circle::getId(void)
{
    return id;
}

void Circle::move()
{
  glPushMatrix();
      glTranslated(center.getX(),center.getY(),0);
      drawCircle();
  glPopMatrix();
}
