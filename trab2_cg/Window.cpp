#include "Window.h"
#include <string>

Window::Window(int w,int h,string c)
{
    width = w;
    height = h;
    background_color = c;
    btn_left = false;
    btn_right = false;
}

Window::Window(int w,int h,double r,double g, double b)
{
    width = w;
    height = h;
    r_color = r;
    g_color = g;
    b_color = b;
    btn_left = false;
    btn_right = false; 
}

Window::Window(string t,int w,int h,string c)
{
    title = t;
    width = w;
    height = h;
    background_color = c;
    btn_left = false;
    btn_right = false;
}

Window::Window(string t,int w,int h,double r,double g, double b)
{
    title = t;
    width = w;
    height = h;
    r_color = r;
    g_color = g;
    b_color = b;
    btn_left = false;
    btn_right = false; 
}


void Window::setWidth(int w)
{
    width = w;
}

void Window::setHeight(int h)
{
    height = h;
}

int Window::getWidth(void)
{
    return width;
}

int Window::getHeight(void)
{
    return height;
}

string Window::getBackgroundColor(void)
{
    return background_color;
}

double Window::getRColor(void)
{
    return r_color;
}

double Window::getGColor(void)
{
    return g_color;
}

double Window::getBColor(void)
{
    return b_color;
}

bool Window::getClickedBtnRight(void)
{
    return btn_right;
}

bool Window::getClickedBtnLeft(void)
{
    return btn_left;
}

bool Window::setClickedBtnRight(bool clicked)
{
    btn_right = clicked;
}

bool Window::setClickedBtnLeft(bool clicked)
{
    btn_left = clicked;
}

bool Window::isPointInWindow(double x, double y)
{
    return (x < getWidth() && y < getHeight() && x > 0 && y > 0);
}

string Window::getTitle(void)
{
    return title;
}

void Window::setTitle(string t)
{
    title = t;
}