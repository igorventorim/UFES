#include <GL/glut.h>
#include "Circle.h"
#include "Window.h"
#include "Scanner.h"
#include <string>
#include <iostream>
#include <cmath>
#include <list>
#define CIRCLE_MINIMUM_SIZE 10


using namespace std;

Circle *circle;
Window *window;
list<Circle*> arena;
int flag=0;

void display(void)
{
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    // if(circle->isDrawn())
    // {
    //     circle->drawCircle();
    // }

    for (std::list<Circle*>::iterator circle=arena.begin(); circle != arena.end(); ++circle)
    {
        (*circle)->drawCircle();
        // cout<<(*circle)->getCoord_x()<<","<<(*circle)->getCoord_y()<<"\n";
        // cout << (*circle)->getRColor() << (*circle)->getGColor()<<(*circle)->getBColor() <<" - "<< (*circle)->getColor()<<"\n" ;
    }
    // flag = 1;
  
    /*Não esperar*/
    glutSwapBuffers();
}

void init(void)
{
	  glClearColor(window->getRColor(),window->getGColor(),window->getBColor(),1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,window->getWidth(),0.0,window->getHeight(),0.0,1.0);
}

void mouse(int button, int state, int x, int y)
{

  // y = window->getHeight() - y;
  // // float position_x = (double)x;///window->getWidth();
  // // float position_y = (double)y;///windstateow->getHeight();
  // if(button == GLUT_LEFT_BUTTON && state )
  // {

  //   if(!circle->isDrawn())
  //   {
  //     circle->setDrawn(true);
  //     circle->setCenter((double)x,(double)y);
  //   }
  //   // window->setClickedBtnRight(false);

  // }else
  //   if(button == GLUT_RIGHT_BUTTON)
  //   {
  //     window->setClickedBtnRight(!state);
  //     circle->setUpdate(circle->pointInCircle(x,y));
  //   }

}

void mouseMotion(int x, int y)
{
  // y = window->getHeight() - y;

	// if(window->getClickedBtnRight() && circle->getUpdate())
	// {
	// 	if(circle->distance2Center(x,y) > CIRCLE_MINIMUM_SIZE && window->isPointInWindow(x,y))
	// 	{
  //     circle->setRadius(circle->distance2Center(x,y));
	// 	}
	// }
	// else
	// if(circle->pointInCircle(x,y) && window->getClickedBtnRight() == false && window->isPointInWindow(x,y))
	// {
  //       circle->setCenter(x,y);
	// }

	// glutPostRedisplay();
}

void idle(void)
{
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
  cout << "Elements in stadium: "<< arena.size() <<"\n\n";
  window = scanner.buildWindowArena(arena);
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
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutMotionFunc(mouseMotion);
	glutMainLoop();


	return 0;
}
