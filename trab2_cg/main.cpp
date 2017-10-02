#include <GL/glut.h>
#include "Circle.h"
#include "Window.h"
#include "Scanner.h"
#include <string>
#include <iostream>
#include <cmath>
#define CIRCLE_MINIMUM_SIZE 10
#define distance_points(x1,x2,y1,y2) sqrt(pow(x1-x2,2)+pow(y1-y2,2))

using namespace std;

Circle *circle;
Window *window;

void display(void)
{
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    if(circle->isDrawn())
    {
        circle->drawCircle();
    }
    /*Não esperar*/
    glutSwapBuffers();
}

void init(void)
{
	  glClearColor(window->getRColor(),window->getGColor(),window->getBColor(),1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,window->getWidth(),0.0,window->getHeight(),-1.0,0.0);
}

void mouse(int button, int state, int x, int y)
{

  y = window->getHeight() - y;
  float position_x = (float)x;///window->getWidth();
  float position_y = (float)y;///windstateow->getHeight();
  if(button == GLUT_LEFT_BUTTON && state )
  {

    if(!circle->isDrawn())
    {
      circle->setDrawn(true);
      circle->setCenter(position_x,position_y);
    }
    // window->setClickedBtnRight(false);

  }else
    if(button == GLUT_RIGHT_BUTTON)
    {
      window->setClickedBtnRight(!state);
      circle->setUpdate(circle->pointInCircle(x,y));
    }

}

void mouseMotion(int x, int y)
{
  y = window->getHeight() - y;

	if(window->getClickedBtnRight() && circle->getUpdate())
	{
		if(circle->distance2Center(x,y) > CIRCLE_MINIMUM_SIZE && window->isPointInWindow(x,y))
		{
      circle->setRadius(circle->distance2Center(x,y));
		}
	}
	else
	if(circle->pointInCircle(x,y) && window->getClickedBtnRight() == false && window->isPointInWindow(x,y))
	{
        circle->setCenter(x,y);
	}

	glutPostRedisplay();
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
  circle = scanner.readCircle(path);

  string title = scanner.readTitle(path);
  window = scanner.readWindow(path);
  glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(window->getWidth(),window->getHeight());
	glutInitWindowPosition(0,0);
	glutCreateWindow(title.data());
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutMotionFunc(mouseMotion);
	glutMainLoop();


	return 0;
}
