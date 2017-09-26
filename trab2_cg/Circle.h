#include <string>

class Circle
{
    private:
        int id;
        string color;
        double radius,coord_x,coord_y;
        double r_color,g_color,b_color;

    public:
        Circle(int,string,double);
        Circle(int,string,double,double,double);
        Circle(int,double,double,double,double);                
        void setRadius(double);
        void setColor(double);
        void setCoord_x(double);
        void setCoord_y(double);
        void setCenter(double,double);
        double getRadius(void);
        double getCoord_x(void);
        double getCoord_y(void);
        string getColor(void);
        double getRColor(void);
        double getGColor(void);
        double getBColor(void);
        
};