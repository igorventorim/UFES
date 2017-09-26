#include <GL/glut.h>
#include "Circle.h"

using namespace std;

void display(void)
{
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
    
    /*Não esperar*/
    glutSwapBuffers();
}

void drawCircle()
{
    
}

void init(void)
{
    // glClearColor(corR_fundo,corG_fundo,corB_fundo,1.0);
    
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(0.0,1.0,0.0,1.0,-1.0,0.0);
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

}


