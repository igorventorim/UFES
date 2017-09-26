#include "Window.h"

Window::Window(int w,int h,string c)
{
    width = w;
    height = h;
    background_color = c;
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