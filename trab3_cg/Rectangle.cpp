#include "Rectangle.h"

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
    /*TODO*/
}
bool Rectangle::isDrawn(void){
    return drawn;
}
