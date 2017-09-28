#include <GL/glut.h>
#include "Circle.h"
#include "Window.h"
#include "Scanner.h"
#include <string>
#include <iostream>

using namespace std;

Circle *circle;
Window *window;

void display(void)
{
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    /*Não esperar*/
    glutSwapBuffers();
}

// void drawCircle()
// {

// }

void init(void)
{
	  glClearColor(window->getRColor(),window->getGColor(),window->getBColor(),1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1.0,0.0,1.0,-1.0,0.0);
}

void mouse(int button, int state, int x, int y)
{

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
	if(argc == 1)
	{
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
