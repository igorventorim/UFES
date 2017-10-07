#include <GL/glut.h>
#include "Circle.h"
#include "Window.h"
#include "Scanner.h"
#include <string>
#include <iostream>
#include <cmath>
#include <list>
#include "Stadium.h"
#define CIRCLE_MINIMUM_SIZE 10


using namespace std;

Stadium *arena;
Window *window;
int key_status[256];
int flag=0;

void display(void)
{
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    arena->drawStadium();

    /*Não esperar*/
    glutSwapBuffers();

}

void init(void)
{
	  glClearColor(window->getRColor(),window->getGColor(),window->getBColor(),1.0);
    glMatrixMode(GL_PROJECTION);
    double dx = arena->getLimiteExterior()->getCoord_x() - arena->getLimiteExterior()->getRadius();
    double dy = arena->getLimiteExterior()->getCoord_y() - arena->getLimiteExterior()->getRadius();

    glOrtho(dx,dx+window->getWidth(),dy,dy+window->getHeight(),0.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y){}

void mouseMotion(int x, int y){}

void keyPress(unsigned char key, int x, int y)
{
	key_status[tolower(key)] = 1;
}

void keyboad_free(unsigned char key,int x, int y)
{
	key_status[tolower(key)] = 0;
}

void timerFunc(int value)
{
  Circle *person = arena->getPerson();
 
  if(!arena->getInLowElements())
  {
    // person->setRadius(person->getRadius()/1.5);
    
    arena->setInLowElements(false);
    arena->setPersonJumping(false);
    flag = 2;
  }else
  {
     arena->setInLowElements(true);
  }
  
  glutPostRedisplay();

}

void idle(void)
{
  Circle *person = arena->getPerson();
  
  if ((key_status['d'] || key_status['D']) && arena->isValidMove(person->getCoord_x()+1,person->getCoord_y()))
  {
    person->moveX(1.0);
  }

  if(( key_status['s'] ||  key_status['S']) && arena->isValidMove(person->getCoord_x(),person->getCoord_y()-1) )
  {
   person->moveY(-1.0);
  }

  if(( key_status['a'] ||  key_status['A'] ) && arena->isValidMove(person->getCoord_x()-1,person->getCoord_y()))
  {
   person->moveX(-1.0);
  }

  if(( key_status['w'] || key_status['W']) && arena->isValidMove(person->getCoord_x(),person->getCoord_y()+1))
  {
    person->moveY(1.0);
  }

  if(!arena->getInLowElements() && arena->getInLow())
  {
    // person->setRadius(person->getRadius()/1.5);
    arena->setInLowElements(false);
    arena->setPersonJumping(false);
    flag = 2;
  }

  if( (key_status['p'] || key_status['P']) && !arena->getPersonJumping() && !arena->getInLowElements())
  {
    // person->setRadius(person->getRadius()*1.5);
    glutTimerFunc(1000,timerFunc,0);
    arena->setPersonJumping(true);
    flag = 1;
  }

  if(flag == 1)
  {
    if(person->getRadius() < arena->getMaxPersonRadius())
    {
      person->setRadius(person->getRadius()+0.2);
    }
  }

  if(flag == 2)
  {
    if(person->getRadius() > arena->getMinPersonRadius())
    {
      person->setRadius(person->getRadius()-0.2);
    }
  }

  glutPostRedisplay();

}

int main(int argc, char **argv)
{
  string path;
  Scanner scanner;
	if(argc == 2)
	{
    cout << argv[0] << "\n";
		path = std::string(argv[1])+"config.xml";
	}else
  {
    cout << "Parâmetros inválidos!!!\n" << "Exemplo: ./trabalhocg /Test1/\n";
    exit(1);
  } 
  string pathSVG = scanner.readConfigXML(path);
  arena = scanner.readArenaSVG(pathSVG);
  window = scanner.buildWindowArena(arena->getLimiteExterior());
  cout << "Size window: "<<window->getWidth() << "x" << window->getHeight()<<"\n";
  glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(window->getWidth(),window->getHeight());
	glutInitWindowPosition(0,0);
	glutCreateWindow(window->getTitle().data());
	init();
	glutDisplayFunc(display);
  glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyboad_free);
	glutMouseFunc(mouse);
  glutIdleFunc(idle);
	glutMotionFunc(mouseMotion);
	glutMainLoop();


	return 0;
}
