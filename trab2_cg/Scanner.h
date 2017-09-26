#include "tinyxml2.h"
#include "Circle.h"
#include "Window.h"

class Scanner
{
    private:
        XMLDocument doc;
    public:
        Scanner();
        Circle readCircle(string);
        string readTitle(string);
        Window readWindow(string);
};