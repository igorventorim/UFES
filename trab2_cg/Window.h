#include <string>

class Window
{
    private:
        int width,height;
        string background_color;
    public:
        Window(int,int,string);
        void setWidth(int);
        void setHeight(int);
        int getWidth(void);
        int getHeight(void);
        string getBackgroundColor(void);

};