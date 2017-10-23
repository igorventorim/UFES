#ifndef _COLOR_H_
#define _COLOR_H_
#include <string>

using namespace std;
class Color
{
	private:
		double r_color,g_color,b_color;
		string colorName;
	public:
		Color();
		Color(string);
		Color(double,double,double);
		double getRColor(void);
        double getGColor(void);
        double getBColor(void);
        void setRColor(double);
        void setGColor(double);
        void setBColor(double);
        void setColorName(string);
        string getColorName(void);
};
#endif