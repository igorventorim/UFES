#include <string>

class Circle
{
    private:
        int id;
        string color;
        double radius,coord_x,coord_y;

    public:
        Circle(int,string,double);
        Circle(int,string,double,double,double);        
        void setRadius(double);
        void setColor(double);
        void setCoord_x(double);
        void setCoord_y(double);
        void setCenter(double,double);
        double getRadius();
        double getCoord_x();
        double getCoord_y();
        string getColor();
        
};