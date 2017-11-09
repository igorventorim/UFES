#include "Shot.h"
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>

Shot::Shot(Circle* s,double v,double a)
{
    shot = s;
    velocity = v;
    angle = a;
}
void Shot::draw()
{
    double newX = shot->getCoord_x() + velocity * cos(angle * M_PI/180);
    double newY = shot->getCoord_y() + velocity * sin(angle * M_PI/180);
    shot->setCoord_x(newX);
    shot->setCoord_y(newY);
    glPushMatrix();
    glTranslatef(newX,newY,0);
    shot->drawCircle();
    glPopMatrix();
}

Circle* Shot::getShot(void)
{
    return shot;
}