#include "Obstacle.h"
#include <GL/gl.h>
#include <GL/glu.h>

Obstacle::Obstacle(Circle* c,double h)
{
    element = c;
    height = h;
}

double Obstacle::getHeight(void)
{
    return height;
}

Circle* Obstacle::getElement(void)
{
    return element;
}

void Obstacle::draw()
{
    glPushMatrix();
    glTranslatef(element->getCoord_x(),element->getCoord_y(),0);
      element->drawCircle();
    glPopMatrix();
}