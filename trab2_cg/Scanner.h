#ifndef _SCANNER_H_
#define _SCANNER_H_

#include "tinyxml2.h"
#include "Circle.h"
#include "Window.h"
#include "Stadium.h"
#include <string>
#include <list>

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
        // list<Circle*> readArenaSVG(string file);
        Stadium* readArenaSVG(string file);
        Window* buildWindowArena(list<Circle*>);
};

#endif
