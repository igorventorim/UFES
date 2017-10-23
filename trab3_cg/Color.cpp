#include "Color.h"


Color::Color(){}

Color::Color(string name)
{	
	colorName = name;
	colorNameToRGB();
}

Color::Color(double r,double g,double b)
{
	r_color = r;
	g_color = g;
	b_color = b;
	rGBToColorName();
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

void Color::colorNameToRGB()
{
   if (colorName == "red")
   {
		r_color = 1.0;
		g_color = 0.0;
		b_color = 0.0;
    }else if(colorName == "blue")
    {
        r_color = 0.0;
        g_color = 0.0;
        b_color = 1.0;
    }else if(colorName == "white")
    {
        r_color = 1.0;
        g_color = 1.0;
        b_color = 1.0;
    }else if(colorName == "black")
    {
        r_color = 0.0;
        g_color = 0.0;
        b_color = 0.0;
    }else if(colorName  == "green")
    {
        r_color = 0.0;
        g_color = 1.0;
        b_color = 0.0;
    }else{
        r_color = 1.0;
        g_color = 1.0;
        b_color = 1.0;
    }
}

void Color::rGBToColorName()
{

	if (r_color == 1.0 && g_color == 0.0 && b_color == 0.0)
	{
		 colorName = "red";
	 }else if(r_color == 0.0 && g_color == 0.0 && b_color == 1.0)
	 {
		 colorName = "blue";
	 }else if(r_color == 1.0 && g_color == 1.0 && b_color == 1.0)
	 {
		 colorName = "white";
	 }else if(r_color == 0.0 && g_color == 0.0 && b_color == 0.0)
	 {
		 colorName = "black";
	 }else if(r_color == 0.0 && g_color == 1.0 && b_color == 0.0)
	 {
		 colorName = "green";
	 }else{
		 colorName = "undefined";
	 }

}