#ifndef _SCANNER_H_
#define _SCANNER_H_

#include "tinyxml2.h"
#include "Circle.h"
#include "Window.h"
#include <string>

using namespace std;
using namespace tinyxml2;

class Scanner
{
    private:
        XMLDocument doc;
    public:
        Scanner();
        Circle* readCircle(string);
        string readTitle(string);
        Window* readWindow(string);
        string readConfigXML(string);
        void readArenaSVG(string file);
};

#endif
