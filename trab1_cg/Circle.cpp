#include "Circle.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include "Point.h"

using namespace std;

Circle::Circle(int identificador, string cor, double raio)
{
    id = id;
    color = color;
    radius = radius;
    drawn = false;
    center = Point();
}

Circle::Circle(int identificador, string cor, double raio, double dX, double dY)
{
    id = id;
    color = color;
    radius = raio;
    // coord_x = dX;
    // coord_y = dY;
    drawn = false;
    center = Point(dX,dY);
}

Circle::Circle(int identificador,double raio ,double r,double g,double b)
{
    id = id;
    radius = raio;
    r_color = r;
    g_color = g;
    b_color = b;
    drawn = false;
}

void Circle::setRadius(double r)
{
    radius = r;
}

void Circle::setColor(double c)
{
    color = c;
}

// void Circle::setCoord_x(double x)
// {
//     coord_x = x;
// }

// void Circle::setCoord_y(double y)
// {
//     coord_y = y;
// }

void Circle::setCenter(double x,double y)
{
    // coord_x = x;
    // coord_y = y;
    center.setPoint2D(x,y);
}

double Circle::getRadius()
{
    return radius;
}

// double Circle::getCoord_x()
// {
//     return coord_x;
// }

// double Circle::getCoord_y()
// {
//     return coord_y;
// }

string Circle::getColor()
{
    return color;
}

double Circle::getRColor(void)
{
    return r_color;
}

double Circle::getGColor(void)
{
    return g_color;
}

double Circle::getBColor(void)
{
    return b_color;
}

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
  /* Limpar todos os pixels  */
  glClear (GL_COLOR_BUFFER_BIT);

  float x2,y2;
  float angle;
  /*double radius=0.2;*/
  glColor3f(getRColor(),getGColor(),getBColor());

  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(center.getX(),center.getY());

  for (angle=0.0f;angle<360.0f;angle+=0.1)
  {
      x2 = center.getX()+sin(angle)*getRadius();
      y2 = center.getY()+cos(angle)*getRadius();
      glVertex2f(x2,y2);
  }
  glEnd();

//   /*Não esperar*/
//   glutSwapBuffers();
//   setDrawn(true);
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

void Circle::setUpdate(bool status)
{
    update = status;
}

bool Circle::getUpdate(void)
{
    return update;
}