#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>

#include "shaderprogram.h"
//#include "object.h"
#include "map.h"
#include "camera.h"

//Macierze
glm::mat4  matP;//rzutowania
glm::mat4  matV;//widoku
glm::mat4  matM;//modelu

//Ustawienia okna i rzutowania
int windowPositionX=100;
int windowPositionY=100;
int windowWidth=400;
int windowHeight=400;
float cameraAngle=45.0f;

//Zmienne do animacji
float speed_x=0; 
float speed_y=0; 
int lastTime=0;
float angle_x=0;
float angle_y=0;

Object *cube, *cube2;
ShaderProgram *shaderProgram; 
Map *map;

// camera(eye,center,nose,ghost_mode_on?)
Camera camera(
	glm::vec3(10.0f, 0.0f, 30.0f), //eye
	glm::vec3(10.0f, 10.0f, 0.0f), //center
	glm::vec3(0.0f, 1.0f, 0.0f), //up
	false
);

void drawObject() {
	map->shaderProgram()->use();
	glUniformMatrix4fv(map->shaderProgram()->getUniformLocation("P"), 1, false, glm::value_ptr(matP));
	glUniformMatrix4fv(map->shaderProgram()->getUniformLocation("V"), 1, false, glm::value_ptr(matV));
	map->manage();
	map->draw();
}

//Procedura rysuj�ca
void displayFrame() {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	matV = camera.lookAt();
	matP = glm::perspective(55.0f, float(windowWidth) / float(windowHeight), 1.0f, 100.0f);
	drawObject();
	glutSwapBuffers();
}

void nextFrame(void) {
	int actTime=glutGet(GLUT_ELAPSED_TIME);
	map->pacman->go();
	for (auto ghost : map->ghosts)
		ghost->go();
	int interval=actTime-lastTime;
	lastTime=actTime;
	camera.update(interval / 1000.0);
	glutPostRedisplay();
}

void timer(int value)
{
	for (auto ghost : map->ghosts)
		ghost->setDirection();
	glutTimerFunc(1000, timer, 0);
}


void specialKeyDown(int c, int x, int y)
{
	switch (c)
	{
		case GLUT_KEY_LEFT:
			map->pacman->goLeft();
			break;
		case GLUT_KEY_RIGHT:
			map->pacman->goRight();
			break;
		case GLUT_KEY_UP:
			map->pacman->goUp();
			break;
		case GLUT_KEY_DOWN:
			map->pacman->goDown();
			break;
	}
}

void keyDown(unsigned char c, int x, int y) {
	switch (c) {
		case 'w':
			camera.keyDown(0);
			break;
		case 's':
			camera.keyDown(1);
			break;
		case 'a':
			camera.keyDown(2);
			break;
		case 'd':
			camera.keyDown(3);
			break;
	}
}

void keyUp(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			camera.keyUp(0);
			break;
		case 's':
			camera.keyUp(1);
			break;
		case 'a':
			camera.keyUp(2);
			break;
		case 'd':
			camera.keyUp(3);
			break;
	}
}

void changeSize(int w, int h) {
	glViewport(0,0,w,h);
	windowWidth=w;
	windowHeight=h;
}

//Procedura inicjuj�ca biblotek� glut
void initGLUT(int *argc, char** argv) {
	glutInit(argc,argv); //Zainicjuj bibliotek� GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Alokuj bufory kolor�w (podw�jne buforowanie) i bufor kolor�w
	
	glutInitWindowPosition(windowPositionX,windowPositionY); //Wska� pocz�tkow� pozycj� okna
	glutInitWindowSize(windowWidth,windowHeight); //Wska� pocz�tkowy rozmiar okna
	glutCreateWindow("OpenGL 3.3"); //Utw�rz okno i nadaj mu tytu�
	
	glutReshapeFunc(changeSize); //Zarejestruj procedur� changeSize jako procedur� obs�uguj�ca zmian� rozmiaru okna
	glutDisplayFunc(displayFrame); //Zarejestruj procedur� displayFrame jako procedur� obs�uguj�ca od�wierzanie okna
	glutIdleFunc(nextFrame); //Zarejestruj procedur� nextFrame jako procedur� wywo�ywan� najcz�ci�j jak si� da (animacja)
	glutTimerFunc(1000, timer, 0);

	glutSpecialFunc(specialKeyDown);
	//glutSpecialUpFunc(specialKeyUp);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
}


//Procedura inicjuj�ca bibliotek� glew
void initGLEW() {
	GLenum err=glewInit();
	if (GLEW_OK!=err) {
		fprintf(stderr,"%s\n",glewGetErrorString(err));
		exit(1);
	}
	
}

int main(int argc, char** argv) {
	initGLUT(&argc,argv);
	initGLEW();

	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
	glEnable(GL_DEPTH_TEST);

	map = new Map();
	glutMainLoop();
	
	delete shaderProgram;
	return 0;
}
