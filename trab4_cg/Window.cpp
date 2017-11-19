#include "Window.h"
#include <string>
#include <iostream>

Window::Window(int w,int h,string c)
{
    width = w;
    height = h;
    background_color = c;
    btn_left = false;
    btn_right = false;
    updateState = false;
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
    updateState = false;
    // colors["black"] = new Color("black");
    // colors["blue"] = new Color("blue");
    // colors["red"] = new Color("red");
}

Window::Window(string t,int w,int h,string c)
{
    title = t;
    width = w;
    height = h;
    background_color = c;
    btn_left = false;
    btn_right = false;
    updateState = false;
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
    updateState = false;
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

bool Window::isUpdateState()
{
    return updateState;
}

void Window::setUpdateState(bool state)
{
    updateState = state;
}

Point* Window::getInitWindow(void)
{
    return initWindow;
}

void Window::setInitWindow(double x, double y)
{
    initWindow= new Point(x,y);
    scorePosition = new Point(initWindow->getX()+ width*0.85,initWindow->getY()+height*0.95);
    msgFinishPosition = new Point(initWindow->getX()+ width*0.43,initWindow->getY()+height*0.48);
}

Point* Window::getScorePosition(void)
{
    return scorePosition;
}

Point* Window::getMsgFinishPosition(void)
{
    return msgFinishPosition;
}

// bool Window::playAgain(void)
// {
//     char c;
//     cout << "Play again [Y/N]: ";
//     cin >> &c;
//     if(c == 'y' || c == 'Y')
//     {
//         return true;
//     }else if(c == 'n' || c == 'N')
//     {
//         exit(0);
        
//     }

//     cout << "Valor inválido tente novamente!\n";
//     return playAgain();
// }

// Color* Window::getColor(string s)
// {
//     // std::map<string,Color*>::iterator it = colors.find(s);
//     // if (it == colors.end()) {
//     //     return NULL;
//     // } else 
//     // {
//     //     return it->second;
//     // }
//     return colors.find(s)->second;
// }