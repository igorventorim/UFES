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
        Stadium* readArenaSVG(string,double,double,double,double,double,double);
    public:
        Scanner();
        Circle* readCircle(string);
        string readTitle(string);
        Window* readWindow(string);
        Stadium* readConfigXML(string);
        // list<Circle*> readArenaSVG(string file);
        Window* buildWindowArena(string,Circle*);
};

#endif
