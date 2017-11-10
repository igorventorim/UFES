#include "Scanner.h"
#include <iostream>
#include <string>
#include <list>
#include "Stadium.h"
#include "Player.h"


using namespace std;
using namespace tinyxml2;

Scanner::Scanner(){}

string Scanner::readTitle(string file)
{
    doc.LoadFile(file.data());
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
    // cout <<  file << "\n";
  	if(!doc.ErrorID())
  	{
          XMLElement* janela = doc.FirstChildElement("aplicacao")->FirstChildElement("janela");
  		janela->FirstChildElement( "largura" )->QueryIntText( &width );
  		janela->FirstChildElement( "altura" )->QueryIntText( &height );
  		janela->FirstChildElement("fundo")->QueryDoubleAttribute("corR",&r_color);
  		janela->FirstChildElement("fundo")->QueryDoubleAttribute("corG",&g_color);
          janela->FirstChildElement("fundo")->QueryDoubleAttribute("corB",&b_color);
          Window* window = new Window(width,height,r_color,g_color,b_color);
          return window;
    }else
  	{
          cout << "Erro ao abrir o arquivo XML "<< file << "\n";
          exit(1);
  	}


}


Stadium* Scanner::readArenaSVG(string file,double velTiro, double vel, double velShotNpc,double velNpc, double heightObstacle, double freqShot )
{
    std::list<Obstacle*> obstacles;
    std::list<NPC*> NPCs;
    Player* person;
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
                Color *cor = new Color(color);
                limiteExterior = new Circle(id,cor,radius,cx,height-cy);
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
            Color *cor = new Color(color);
            if(color == "black")
            {
              Circle* circle = new Circle(id,cor,radius,cx,height-cy);
              Obstacle *obstacle = new Obstacle(circle,heightObstacle);
              obstacles.push_back(obstacle);
            }else if(color == "red")
            {
              Circle* circle = new Circle(id,cor,radius/1.8,cx,height-cy);
              NPC* npc = new NPC(circle,velShotNpc,velNpc);
              NPCs.push_back(npc);
            }else if(color == "white")
            {
              limiteInterior = new Circle(id,cor,radius,cx,height-cy);
            }else if(color == "green")
            {
              person = new Player(new Circle(id,cor,radius/1.8,cx,height-cy),velTiro,vel);
            }
        }

        stadium = new Stadium(limiteExterior,limiteInterior,person,NPCs,obstacles,freqShot);
        return stadium;
  }else
    {
        cout << "Erro ao abrir o arquivo XML "<< file << "\n";
        exit(1);
    }

}

Stadium* Scanner::readConfigXML(string file)
{
    string name, type, path;
    double shot, move;
    double npcVel, shotNpc, alturaObstaculo, freqTiro;

    doc.LoadFile(file.data());
    if(!doc.ErrorID())
    {
        XMLElement* arena = doc.FirstChildElement("aplicacao")->FirstChildElement("arquivoDaArena");
        name = arena->Attribute("nome");
        type = arena->Attribute("tipo");
        path = arena->Attribute("caminho");
        XMLElement* player = doc.FirstChildElement("aplicacao")->FirstChildElement("jogador");
        player->QueryDoubleAttribute("velTiro",&shot);
        player->QueryDoubleAttribute("vel",&move);

        XMLElement* inimigo = doc.FirstChildElement("aplicacao")->FirstChildElement("inimigo");
        inimigo->QueryDoubleAttribute("velTiro",&shotNpc);
        inimigo->QueryDoubleAttribute("vel",&npcVel);
        inimigo->QueryDoubleAttribute("freqTiro",&freqTiro);

        XMLElement* obstacle = doc.FirstChildElement("aplicacao")->FirstChildElement("obstaculo");
        obstacle->QueryDoubleAttribute("altura",&alturaObstaculo);
        return readArenaSVG(path + name +"."+type,shot,move,shotNpc,npcVel,alturaObstaculo,freqTiro);
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
