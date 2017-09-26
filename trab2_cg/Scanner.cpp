#include "Scanner.h"
#include <iostream>

using namespace std;
using namespace tinyxml2;

Scanner::Scanner(){}

Circle Scanner::readCircle(string file)
{
    int radius;
    double r_color,g_color,b_color;
    doc.LoadFile(file.data());
    cout <<  file << "\n";
	if(!doc.ErrorID())
	{
        XMLElement* circulo = doc.FirstChildElement("aplicacao")->FirstChildElement("circulo");
		circulo->QueryIntAttribute("raio",&radius);
		circulo->QueryValueAttribute("corR",&r_color);
		circulo->QueryValueAttribute("corG",&g_color);
        circulo->QueryValueAttribute("corB",&b_color);
        // string color = "#"+std::to_string(r_color)+"#"+std::to_string(g_color)+"#"+std::to_string(b_color);
        Circle circle(0,radius,r_color,g_color,b_color);
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

Window Scanner::readWindow(string file)
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
		janela->FirstChildElement("fundo")->QueryValueAttribute("corR",&r_color);
		janela->FirstChildElement("fundo")->QueryValueAttribute("corG",&g_color);
        janela->FirstChildElement("fundo")->QueryValueAttribute("corB",&b_color);
        
        // string color = "#"+std::to_string(r_color)+"#"+std::to_string(g_color)+"#"+std::to_string(b_color);
        Window window(width,height,r_color,g_color,b_color);
        return window;
    }else
	{
        cout << "Erro ao abrir o arquivo XML "<< file << "\n";
        return NULL;
	}
}