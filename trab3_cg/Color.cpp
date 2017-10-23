#include "Color.h"


Color::Color(){}

Color::Color(string name)
{	
	colorName = name;
}

Color::Color(double r,double g,double b)
{
	r_color = r;
	g_color = g;
	b_color = b;
}
double Color::getRColor(void)
{
	return r_color;
}
double Color::getGColor(void)
{
	return g_color;
}
double Color::getBColor(void)
{
	return b_color;
}
void Color::setRColor(double value)
{
	r_color = value;
}
void Color::setGColor(double value)
{
	g_color = value;
}
void Color::setBColor(double value)
{
	b_color = value;
}
void Color::setColorName(string name)
{
	colorName = name;
}
string Color::getColorName(void)
{
	return colorName;
}