#include "NPC.h"

NPC::NPC(Circle* circle, double shot, double move): Person(circle,shot,move)
{

}

bool NPC::isMe(Person* p)
{
    if(getCoord_x() == p->getCoord_x() && getCoord_y() == p->getCoord_y())
    {
        return true;
    }else
    {
        return false;
    }
}