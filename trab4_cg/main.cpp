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
#include "GeneticAlgorithm.h"

using namespace std;

Stadium *arena;
Window *window;
int key_status[256];
bool finished = false;
std::chrono::time_point<std::chrono::system_clock> frameTime;
double dShot = 0;
Color *black = new Color("black");
Color *blue = new Color("blue");
Color *red = new Color("red");
GeneticAlgorithm* ga = new GeneticAlgorithm();



void display(void) {

	Point *initWindow = window->getInitWindow();

	/* Limpar todos os pixels  */
	glClear (GL_COLOR_BUFFER_BIT);

	arena->drawStadium();
	arena->drawText(black,window->getScorePosition(),"Score: "+std::to_string(arena->getScore()));

	if(finished)
	{	if(arena->isWin())
		{
			arena->drawText(blue,window->getMsgFinishPosition(),"You Win! :)");
		}else{
			arena->drawText(red,window->getMsgFinishPosition(),"You Loser... :(");
		}
	}

	/*Não esperar*/
	glutSwapBuffers();

	if(finished)
	{
		finished = !window->playAgain();
	}
}

void init(void) {
	glClearColor(window->getRColor(), window->getGColor(), window->getBColor(),
			1.0);
	glMatrixMode (GL_PROJECTION);
	double dx = arena->getLimiteExterior()->getCoord_x()
			- arena->getLimiteExterior()->getRadius();
	double dy = arena->getLimiteExterior()->getCoord_y()
			- arena->getLimiteExterior()->getRadius();
	window->setInitWindow(dx,dy);

	glOrtho(dx, dx + window->getWidth(), dy, dy + window->getHeight(), 0.0,
			1.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	frameTime = std::chrono::system_clock::now();
}

void mouse(int button, int state, int x, int y)
{
	Player *p = arena->getPlayer();
	if(GLUT_LEFT_BUTTON == button && state && !arena->getPersonJumping(p) && !p->isOnElement() )
	{
		Shot *s = p->atirar();
		arena->addShotPlayer(s);
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


void moveNPC(NPC *person)
{
	if ((person)->getCurrentMovement()[3]
			&& arena->isValidMove(-1,person)) {
		person->setDown(true);
		person->moveDown();
	}

	if ((person)->getCurrentMovement()[1]) {
		person->rotateLeft();
	}

	if ((person)->getCurrentMovement()[0]) {
		person->rotateRight();
	}

	if ((person)->getCurrentMovement()[2]
			&& arena->isValidMove(1,person)) {
		person->moveUp();
	}

	if ((person)->getCurrentMovement()[4]) {
		person->jump();
	}

	if(person->isJumping() || person->getResize() || person->isJumpingOnElement())
	{
		person->changeSize();
	}

}


void idle(void) {
	Player *person = arena->getPlayer();
	list<NPC*> npcs = arena->getNPCs();
	ga->modifyRun(npcs);

	if ((key_status['s'] || key_status['S'])
			&& arena->isValidMove(-1,person)) {
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
			&& arena->isValidMove(1,person)) {
		person->moveUp();
	}

	if ((key_status['p'] || key_status['P'])) {
		person->jump();
	}

	if(person->isJumping() || person->getResize() || person->isJumpingOnElement())
	{
		person->changeSize();
	}

	if(arena->checkShotPlayer())
	{
		arena->setWin(true);
		finished = true;
	}

	if(arena->checkShotNPC())
	{
		arena->setWin(false);
		finished = true;
	}

	if(dShot > 1000/arena->getFreqShotNPC())
	{
		arena->shootShotsNPCs();
		dShot = 0;
	}

	// arena->changeSizeNPCs();

	for (std::list<NPC*>::iterator npc=npcs.begin(); npc != npcs.end(); ++npc)
	{
		moveNPC((*npc));
		(*npc)->setDown(false);
	}


	// arena->moveNPC();

	double elapsed = std::chrono::duration_cast<std::chrono::milliseconds> ( std::chrono::system_clock::now() - frameTime).count();
	Stadium::MILLISECONDS_BY_FRAME = elapsed;
	glutPostRedisplay();
	frameTime = std::chrono::system_clock::now();
	dShot += Stadium::MILLISECONDS_BY_FRAME;
	person->setDown(false);
}


int main(int argc, char **argv) {
	string path;
	Scanner scanner;
	if (argc == 2) {
		path = std::string(argv[1]) + "config.xml";
	} else {
		cout << "Parâmetros inválidos!!!\n"
				<< "Exemplo: ./trabalhocg /Test1/\n";
		exit(1);
	}
	arena = scanner.readConfigXML(path);
	window = scanner.buildWindowArena(path, arena->getLimiteExterior());
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
