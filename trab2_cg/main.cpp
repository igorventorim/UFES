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
// Circle *person;
Window *window;
// list<Circle*> arena;
int key_status[256];
int flag=0;

void display(void)
{
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    // if(window->isUpdateState())
    // {
      arena->drawStadium();
      // glClear (GL_COLOR_BUFFER_BIT);
      // for (std::list<Circle*>::iterator circle=arena.begin(); circle != arena.end(); ++circle)
      // {
      //     (*circle)->drawCircle();
      //     if((*circle)->getColor() == "green")
      //     {
      //       person = *circle;
      //     }
      //     // cout<<(*circle)->getCoord_x()<<","<<(*circle)->getCoord_y()<<"\n";
      //     // cout << (*circle)->getRColor() << (*circle)->getGColor()<<(*circle)->getBColor() <<" - "<< (*circle)->getColor()<<"\n" ;

      // }
      
    // }
    // person->move();
    // person->drawCircle();
    /*Não esperar*/
    glutSwapBuffers();

}

void init(void)
{
	  glClearColor(window->getRColor(),window->getGColor(),window->getBColor(),1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(200.00,200.00+window->getWidth(),-200.00,window->getHeight()-200.00,0.0,1.0);
}

void mouse(int button, int state, int x, int y)
{

}

void mouseMotion(int x, int y)
{

}

void keyPress(unsigned char key, int x, int y)
{
	key_status[tolower(key)] = 1;
  window->setUpdateState(true);
}

void keyboad_free(unsigned char key,int x, int y)
{
	key_status[tolower(key)] = 0;

  window->setUpdateState(false);
}

void idle(void)
{
	 if (key_status['d'] || key_status['D'])
	 {
		//  d_x+=0.01;
    // person->setCoord_x(person->getCoord_x()+1);
	 }

	 if( key_status['s'] ||  key_status['S'])
	 {
		//  d_y-=0.01;
    // person->setCoord_y(person->getCoord_y()-1);
	 }

	 if( key_status['a'] ||  key_status['A'] )
	 {
		//  d_x-=0.01;
    // person->setCoord_x(person->getCoord_x()-1);
	 }

	 if( key_status['w'] || key_status['W'])
	 {
		//  d_y+=0.01;
    // person->setCoord_y(person->getCoord_y()+1);
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
	}else{
        cout << "Parâmetros inválidos!!!\n" << "Exemplo: ./trabalhocg /Test1/\n";
        exit(1);
    }
  string pathSVG = scanner.readConfigXML(path);
  arena = scanner.readArenaSVG(pathSVG);
  // cout << "Elements in stadium: "<< arena.size() <<"\n\n";
  window = scanner.buildWindowArena(arena->getObjects());
  cout << "Size window: "<<window->getWidth() << "x" << window->getHeight()<<"\n";
  // circle = scanner.readCircle(path);
  // string title = scanner.readTitle(path);
  // window = scanner.readWindow(path);
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
