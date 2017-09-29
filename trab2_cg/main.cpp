#include <GL/glut.h>
#include "Circle.h"
#include "Window.h"
#include "Scanner.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
void drawCircle();
Circle *circle;
Window *window;

void display(void)
{
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    if(circle->isDrawn())
    {
        drawCircle();
    }

    /*Não esperar*/
    glutSwapBuffers();
}

void drawCircle()
{
  /* Limpar todos os pixels  */
  glClear (GL_COLOR_BUFFER_BIT);

  float x2,y2;
  float angle;
  /*double radius=0.2;*/
  glColor3f(circle->getRColor(),circle->getGColor(),circle->getBColor());

  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(circle->getCoord_x(),circle->getCoord_y());

  for (angle=0.0f;angle<360.0f;angle+=0.1)
  {
      x2 = circle->getCoord_x()+sin(angle)*circle->getRadius();
      y2 = circle->getCoord_y()+cos(angle)*circle->getRadius();
      glVertex2f(x2,y2);
  }
  glEnd();

  /*Não esperar*/
  glutSwapBuffers();
}

void init(void)
{
	  glClearColor(window->getRColor(),window->getGColor(),window->getBColor(),1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1.0,0.0,1.0,-1.0,0.0);
}

void mouse(int button, int state, int x, int y)
{

  y = window->getHeight() - y;
  float position_x = (float)x/window->getWidth();
  float position_y = (float)y/window->getHeight();
  if(button == GLUT_LEFT_BUTTON && state )
  {

    if(!circle->isDrawn())
    {
      circle->setDrawn(true);
      circle->setCenter(position_x,position_y);
    }
    // button_right = 0;

  }//else
    // if(button == GLUT_RIGHT_BUTTON)
    // {
    //   button_right = !state;
    //   in = distance_points(position_x,d_x,position_y,d_y) < radius;
    // }

}

void mouseMotion(int x, int y)
{

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
