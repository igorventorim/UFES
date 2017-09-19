#include "tinyxml2.h"
#include <GL/glut.h>
#include <iostream>
#include <ctype.h>
#include <cmath>
#include <limits.h>

#define distance_points(x1,x2,y1,y2) sqrt(pow(x1-x2,2)+pow(y1-y2,2))

using namespace std;
using namespace tinyxml2;

float d_x = 0.0;
float d_y = 0.0;
int width;
int height;
double radius;
void drawCircle();
int button_right;
bool in;
bool started = false;
string title;
int corR_circulo, corG_circulo, corB_circulo;
int corR_fundo,corG_fundo,corB_fundo;

void display(void)
{
	/* Limpar todos os pixels  */
	glClear (GL_COLOR_BUFFER_BIT);

	if(started)
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

	 float x1,y1,x2,y2;
	 float angle;
	 /*double radius=0.2;*/
	 glColor3f(corR_circulo,corG_circulo,corB_circulo);

	 glBegin(GL_TRIANGLE_FAN);
	 glVertex2f(d_x,d_y);

	 for (angle=0.0f;angle<360.0f;angle+=0.1)
	 {
			 x2 = d_x+sin(angle)*radius;
			 y2 = d_y+cos(angle)*radius;
			 glVertex2f(x2,y2);
	 }

	 glEnd();

	 /*Não esperar*/
	 glutSwapBuffers();
}


void init(void)
{

	glClearColor(corR_fundo,corG_fundo,corB_fundo,1.0);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,0.0);
}

void mouse(int button, int state, int x, int y)
{
	 y = height - y;
	 float position_x = (float)x/width;
	 float position_y = (float)y/height;
	 if(button == GLUT_LEFT_BUTTON && state )
	 {

		 if(!started)
		 {
			 started = true;
			 d_x = position_x;
			 d_y = position_y;
		 }
		 button_right = 0;

	 }else
		 if(button == GLUT_RIGHT_BUTTON)
		 {
			 button_right = !state;
			 in = distance_points(position_x,d_x,position_y,d_y) < radius;
		 }
}


void mouseMotion(int x, int y)
{
	
	y = height - y;
	float position_x = (float)x/width;
	float position_y = (float)y/height;

	if(button_right && in)
	{
		if(distance_points(position_x,d_x,position_y,d_y) > 0.05 )
		{
			radius = distance_points(position_x,d_x,position_y,d_y);
		}
	}
	else
	if(distance_points(position_x,d_x,position_y,d_y) < radius && !button_right)
	{
				d_x = position_x;
				d_y = position_y;
	}

	glutPostRedisplay();
}

void idle(void)
{
	glutPostRedisplay();
}


int readFile(string file)
{
	XMLDocument doc;
	doc.LoadFile(file.data());
	cout <<  file << "\n";
	if(!doc.ErrorID())
	{
		int raio_circulo;
		
		XMLElement* janela = doc.FirstChildElement("aplicacao")->FirstChildElement("janela");
		const char *titulo = janela->FirstChildElement("titulo")->GetText();
		janela->FirstChildElement( "largura" )->QueryIntText( &width );
		janela->FirstChildElement( "altura" )->QueryIntText( &height );
		janela->FirstChildElement("fundo")->QueryIntAttribute("corR",&corR_fundo);
		janela->FirstChildElement("fundo")->QueryIntAttribute("corG",&corG_fundo);
		janela->FirstChildElement("fundo")->QueryIntAttribute("corB",&corB_fundo);
		
		XMLElement* circulo = doc.FirstChildElement("aplicacao")->FirstChildElement("circulo");
		circulo->QueryIntAttribute( "raio", &raio_circulo);
		circulo->QueryIntAttribute("corR",&corR_circulo);
		circulo->QueryIntAttribute("corG",&corG_circulo);
		circulo->QueryIntAttribute("corB",&corB_circulo);
		

		title = std::string(titulo);
		radius = raio_circulo/(double)width;
	}else
	{
		cout << "Erro ao abrir o arquivo XML "<< file << "\n";
	}	
	return doc.ErrorID();
}

int main(int argc, char **argv)
{
	string path;
	// if(argc > 1 && (argv[1][1] != '.' && !(std::string(argv[1]).find("/home"))))
	// {
	// 		path = "."+std::string(argv[1])+"config.xml";	
	// }else if(argc > 1 && (argv[1][1] == '.' || (std::string(argv[1]).find("/home"))))
	// {
	// 	path = std::string(argv[1])+"config.xml";
	// }else
	// {
	// 	path += "config.xml";
	// }
	if(argc > 1)
	{
		path = std::string(argv[1])+"config.xml";
	}else
	{
		path = "config.xml";
	}

	readFile(path);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width,height);
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
