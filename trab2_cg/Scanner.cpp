#include "Scanner.h"
#include <iostream>
#include <string>
#include <list>


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

list<Circle*> Scanner::readArenaSVG(string file)
{
    std::list<Circle*> list;
    double cx,cy,radius;
    int id;
    string color;
    doc.LoadFile(file.data());
    if(!doc.ErrorID())
    {
        XMLElement* circle = doc.FirstChildElement("svg");
        for( circle = circle->FirstChildElement("circle"); circle != NULL; circle = circle->NextSiblingElement("circle"))
        {
            circle->QueryDoubleAttribute("r",&radius);
            circle->QueryDoubleAttribute("cx",&cx);
            circle->QueryDoubleAttribute("cy",&cy);
            circle->QueryIntAttribute("id",&id);
            color = circle->Attribute("fill");
            // cout << "cx:" << cx <<"\ncy:"<< cy<<"\nradius:"<<radius<<"\ncolor:"<< color <<"\nid:"<<id<<"\n\n";
            // Circle* circle = new Circle(id,color,radius,cx,cy);
            Circle* circle = new Circle(id,color,radius,cx,cy);
            // Circle *circle = new Circle(0,radius,1.0,1.0,1.0);

            list.push_back(circle);
        }
        return list;
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

Window* Scanner::buildWindowArena(list<Circle*> mylist)
{
    Window* window;
    for (std::list<Circle*>::iterator it=mylist.begin(); it != mylist.end(); ++it)
    {
        if((*it)->getId() == 1)
        {
            window = new Window("Arena",(*it)->getRadius()*2,(*it)->getRadius()*2,1.0,1.0,1.0);
        }
    }

    return window;
}
