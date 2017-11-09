#ifndef _SHOT_H_
#define _SHOT_H_
#include "Circle.h"

class Shot{
    private:
        Circle* shot;
        double velocity;
        double angle;
    public:
        Shot(Circle*,double,double);
        Circle* getShot(void);
        void draw();
};

#endif