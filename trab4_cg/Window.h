#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <string>
#include "Point.h"
#include "Color.h"
#include <map>

using namespace std;

class Window
{
    private:
        int width,height;
        string title;
        string background_color;
        double r_color,g_color,b_color;
        bool btn_right, btn_left;
        bool updateState;
        double coord_initWindowX;
        double coord_initWindowY;
        Point *initWindow;
        Point *scorePosition;
        Point *msgFinishPosition;
        // std::map<std::string, Color*> colors;
    public:
        Window(int,int,string);
        Window(int,int,double,double,double);
        Window(string,int,int,string);
        Window(string,int,int,double,double,double);
        void setWidth(int);
        void setHeight(int);
        int getWidth(void);
        int getHeight(void);
        double getRColor(void);
        double getGColor(void);
        double getBColor(void);
        string getBackgroundColor(void);
        bool getClickedBtnRight(void);
        bool getClickedBtnLeft(void);
        bool setClickedBtnRight(bool);
        bool setClickedBtnLeft(bool);
        bool isPointInWindow(double, double);
        string getTitle(void);
        void setTitle(string);
        bool isUpdateState();
        void setUpdateState(bool);
        Point* getInitWindow(void);
        void setInitWindow(double,double);
        Point* getScorePosition(void);
        Point* getMsgFinishPosition(void);
        bool playAgain(void);
        // Color* getColor(string);
        // double getCoord_initWindowX(void);
        // double getCoord_initWindowY(void);
        // void setCoord_initWindowX(double);
        // void setCoord_initWindowY(double);

};
#endif
