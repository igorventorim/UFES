#include "Window.h"
#include <string>

Window::Window(int w,int h,string c)
{
    width = w;
    height = h;
    background_color = c;
}

Window::Window(int w,int h,double r,double g, double b)
{
    width = w;
    height = h;
    r_color = r;
    g_color = g;
    b_color = b;
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
