#include "Scanner.h"
#include <iostream>
#include <string>
#include <list>
#include "Stadium.h"


using namespace std;
using namespace tinyxml2;

Scanner::Scanner(){}

Circle* Scanner::readCircle(string file)
{
    int radius;
    double r_color,g_color,b_color;
    doc.LoadFile(file.data());
    // cout <<  file << "\n";
  	if(!doc.ErrorID())
  	{
          XMLElement* circulo = doc.FirstChildElement("aplicacao")->FirstChildElement("circulo");
  		    circulo->QueryIntAttribute("raio",&radius);
  	 	    circulo->QueryDoubleAttribute("corR",&r_color);
  		    circulo->QueryDoubleAttribute("corG",&g_color);
          circulo->QueryDoubleAttribute("corB",&b_color);
          // string color = "#"+std::to_string(r_color)+"#"+std::to_string(g_color)+"#"+std::to_string(b_color);
          Circle *circle = new Circle(0,radius,r_color,g_color,b_color);
          return circle;
    }else
  	{
  		cout << "Erro ao abrir o arquivo XML "<< file << "\n";
  	}

}

string Scanner::readTitle(string file)
{
    doc.LoadFile(file.data());
    cout <<  file << "\n";
  	if(!doc.ErrorID())
  	{
          XMLElement* janela = doc.FirstChildElement("aplicacao")->FirstChildElement("janela");
          const char *titulo = janela->FirstChildElement("titulo")->GetText();
          return std::string(titulo);
      }else
  	{
          cout << "Erro ao abrir o arquivo XML "<< file << "\n";
          return NULL;
  	}
}

Window* Scanner::readWindow(string file)
{
    int width,height;
    double r_color,g_color,b_color;
    doc.LoadFile(file.data());
    cout <<  file << "\n";
  	if(!doc.ErrorID())
  	{
          XMLElement* janela = doc.FirstChildElement("aplicacao")->FirstChildElement("janela");
  		janela->FirstChildElement( "largura" )->QueryIntText( &width );
  		janela->FirstChildElement( "altura" )->QueryIntText( &height );
  		janela->FirstChildElement("fundo")->QueryDoubleAttribute("corR",&r_color);
  		janela->FirstChildElement("fundo")->QueryDoubleAttribute("corG",&g_color);
          janela->FirstChildElement("fundo")->QueryDoubleAttribute("corB",&b_color);

          // string color = "#"+std::to_string(r_color)+"#"+std::to_string(g_color)+"#"+std::to_string(b_color);
          Window* window = new Window(width,height,r_color,g_color,b_color);
          return window;
    }else
  	{
          cout << "Erro ao abrir o arquivo XML "<< file << "\n";
          exit(1);
  	}


}


Stadium* Scanner::readArenaSVG(string file)
{
    // std::list<Circle*> list;
    std::list<Circle*> lowElements;
    std::list<Circle*> hightElements;
    Circle* person;
    Circle* limiteInterior;
    Circle* limiteExterior;

    Stadium *stadium;
    XMLElement* circle;
    double cx,cy,radius,height;
    int id;
    string color;
    doc.LoadFile(file.data());

    if(!doc.ErrorID())
    {
        circle = doc.FirstChildElement("svg");
        for( circle = circle->FirstChildElement("circle"); circle != NULL; circle = circle->NextSiblingElement("circle"))
        {
            circle->QueryDoubleAttribute("r",&radius);
            circle->QueryDoubleAttribute("cx",&cx);
            circle->QueryDoubleAttribute("cy",&cy);
            circle->QueryIntAttribute("id",&id);
            color = circle->Attribute("fill");
            if(color == "blue")
            {
                height = radius*2;
                limiteExterior = new Circle(id,color,radius,cx,height-cy);
            }

        }

        circle = doc.FirstChildElement("svg");
        for( circle = circle->FirstChildElement("circle"); circle != NULL; circle = circle->NextSiblingElement("circle"))
        {
            circle->QueryDoubleAttribute("r",&radius);
            circle->QueryDoubleAttribute("cx",&cx);
            circle->QueryDoubleAttribute("cy",&cy);
            circle->QueryIntAttribute("id",&id);
            color = circle->Attribute("fill");

            if(color == "black")
            {
              Circle* circle = new Circle(id,color,radius,cx,height-cy);
              lowElements.push_back(circle);
            }else if(color == "red")
            {
              Circle* circle = new Circle(id,color,radius,cx,height-cy);
              hightElements.push_back(circle);
            }else if(color == "white")
            {
              limiteInterior = new Circle(id,color,radius,cx,height-cy);
            }else if(color == "green")
            {
              person = new Circle(id,color,radius,cx,height-cy);
            }
        }

        stadium = new Stadium(limiteExterior,limiteInterior,person,hightElements,lowElements);
        return stadium;
  }else
    {
        cout << "Erro ao abrir o arquivo XML "<< file << "\n";
        exit(1);
    }

}

string Scanner::readConfigXML(string file)
{
    string name, type, path;
    doc.LoadFile(file.data());
    if(!doc.ErrorID())
    {
        XMLElement* arena = doc.FirstChildElement("aplicacao")->FirstChildElement("arquivoDaArena");
        name = arena->Attribute("nome");
        type = arena->Attribute("tipo");
        path = arena->Attribute("caminho");

        return path + name +"."+type;
  }else
    {
        cout << "Erro ao abrir o arquivo XML "<< file << "\n";
        exit(1);
    }

}

Window* Scanner::buildWindowArena(string file,Circle* limiteExterior)
{
    doc.LoadFile(file.data());
    XMLElement* arena = doc.FirstChildElement("aplicacao")->FirstChildElement("arquivoDaArena");
    string name = arena->Attribute("nome");
    Window* window = new Window(name,limiteExterior->getRadius()*2,limiteExterior->getRadius()*2,1.0,1.0,1.0);
    return window;
}
