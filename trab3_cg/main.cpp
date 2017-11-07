#include <GL/glut.h>
#include "Circle.h"
#include "Window.h"
#include "Scanner.h"
#include <string>
#include <iostream>
#include <cmath>
#include <list>
#include <chrono>
#include <ctime>
#include "Stadium.h"
#include "Shot.h"
#define CIRCLE_MINIMUM_SIZE 10

using namespace std;

Stadium *arena;
Window *window;
int key_status[256];
std::chrono::time_point<std::chrono::system_clock> frameTime;

void display(void) {
	/* Limpar todos os pixels  */
	glClear (GL_COLOR_BUFFER_BIT);

	arena->drawStadium();

	/*Não esperar*/
	glutSwapBuffers();

}

void init(void) {
	glClearColor(window->getRColor(), window->getGColor(), window->getBColor(),
			1.0);
	glMatrixMode (GL_PROJECTION);
	double dx = arena->getLimiteExterior()->getCoord_x()
			- arena->getLimiteExterior()->getRadius();
	double dy = arena->getLimiteExterior()->getCoord_y()
			- arena->getLimiteExterior()->getRadius();

	glOrtho(dx, dx + window->getWidth(), dy, dy + window->getHeight(), 0.0,
			1.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	frameTime = std::chrono::system_clock::now();
}

void mouse(int button, int state, int x, int y) 
{
	Player *p = arena->getPlayer();
	if(GLUT_LEFT_BUTTON == button && state && !arena->getPersonJumping() && !p->isOnElement() )
	{	
		Shot *s = p->atirar();
		arena->addShot(s);
	}
}

void mouseMotion(int x, int y) {}

void mousePassiveMotion(int x, int y)
{
	arena->getPlayer()->moveHand(x,y - window->getHeight());
}

void keyPress(unsigned char key, int x, int y) {
	key_status[tolower(key)] = 1;
}

void keyboad_free(unsigned char key, int x, int y) {
	key_status[tolower(key)] = 0;
}

void idle(void) {
	Player *person = arena->getPlayer();

	if ((key_status['s'] || key_status['S'])
			&& arena->isValidMove(-1)) {
		person->setDown(true);
		person->moveDown();
	}

	if ((key_status['a'] || key_status['A'])) {
		person->rotateLeft();
	}

	if ((key_status['d'] || key_status['D'])) {
		person->rotateRight();	
	}

	if ((key_status['w'] || key_status['W'])
			&& arena->isValidMove(1)) {
		person->moveUp();
	}

	if ((key_status['p'] || key_status['P']) && !person->isJumping()
			&& !person->isOnElement()) {
		person->jump();
	}

	if(person->isJumping())
	{
		person->changeSize();
	}

	double elapsed = std::chrono::duration_cast<std::chrono::milliseconds> ( std::chrono::system_clock::now() - frameTime).count();	
	Stadium::MILLISECONDS_BY_FRAME = elapsed;
	glutPostRedisplay();
	frameTime = std::chrono::system_clock::now();
	person->setDown(false);
}

int main(int argc, char **argv) {
	string path;
	Scanner scanner;
	if (argc == 2) {
		cout << argv[0] << "\n";
		path = std::string(argv[1]) + "config.xml";
	} else {
		cout << "Parâmetros inválidos!!!\n"
				<< "Exemplo: ./trabalhocg /Test1/\n";
		exit(1);
	}
	arena = scanner.readConfigXML(path);
	window = scanner.buildWindowArena(path, arena->getLimiteExterior());
	cout << "Size window: " << window->getWidth() << "x" << window->getHeight()
			<< "\n";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(window->getWidth(), window->getHeight());
	glutInitWindowPosition(0, 0);
	glutCreateWindow(window->getTitle().data());
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyboad_free);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutMainLoop();

	return 0;
}
