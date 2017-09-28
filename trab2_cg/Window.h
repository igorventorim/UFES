#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <string>

using namespace std;

class Window
{
    private:
        int width,height;
        string background_color;
        double r_color,g_color,b_color;
    public:
        Window(int,int,string);
        Window(int,int,double,double,double);
        void setWidth(int);
        void setHeight(int);
        int getWidth(void);
        int getHeight(void);
        double getRColor(void);
        double getGColor(void);
        double getBColor(void);
        string getBackgroundColor(void);

};
#endif
