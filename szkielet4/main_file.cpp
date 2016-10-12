#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <cstdio>
#include <string>

#include "shaderprogram.h"
//#include "object.h"
#include "map.h"
#include "camera.h"
#include "text_renderer.h"

//Macierze
glm::mat4  matP;//rzutowania
glm::mat4  matV;//widoku
glm::mat4  matM;//modelu

//Ustawienia okna i rzutowania
int windowPositionX=100;
int windowPositionY=100;
int windowWidth=800;
int windowHeight=600;
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
TextRenderer *textRenderer;

// camera(eye,center,nose,ghost_mode_on?)
Camera camera(
	glm::vec3(15.0f, 0.0f, 40.0f), //eye
	glm::vec3(15.0f, 15.0f, 0.0f), //center
	glm::vec3(0.0f, 1.0f, 0.0f), //up
	true
);

void drawObject() {
	map->shaderProgram()->use();
	glUniformMatrix4fv(map->shaderProgram()->getUniformLocation("P"), 1, false, glm::value_ptr(matP));
	glUniformMatrix4fv(map->shaderProgram()->getUniformLocation("V"), 1, false, glm::value_ptr(matV));
	map->draw();
	switch (map->checkState())
	{
		case 0: textRenderer->renderText(std::to_string(map->getRemainedFood()) + " remaining", 30, 30, 0.8f, glm::vec3(1, 1, 1));
			break;
		case 1: textRenderer->renderText("You win!", 30, 30, 0.8f, glm::vec3(1, 1, 1));
			break;
		case -1: textRenderer->renderText("You lose!", 30, 30, 0.8f, glm::vec3(1, 1, 1));
			break;
	}	
}

//Procedura rysuj¹ca
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
		case 'r':
			map->reset();
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
	textRenderer->resizeWindow(windowWidth, windowHeight);
}

//Procedura inicjuj¹ca biblotekê glut
void initGLUT(int *argc, char** argv) {
	glutInit(argc,argv); //Zainicjuj bibliotekê GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Alokuj bufory kolorów (podwójne buforowanie) i bufor kolorów
	
	glutInitWindowPosition(windowPositionX,windowPositionY); //Wska¿ pocz¹tkow¹ pozycjê okna
	glutInitWindowSize(windowWidth,windowHeight); //Wska¿ pocz¹tkowy rozmiar okna
	glutCreateWindow("OpenGL 3.3"); //Utwórz okno i nadaj mu tytu³
	
	glutReshapeFunc(changeSize); //Zarejestruj procedurê changeSize jako procedurê obs³uguj¹ca zmianê rozmiaru okna
	glutDisplayFunc(displayFrame); //Zarejestruj procedurê displayFrame jako procedurê obs³uguj¹ca odœwierzanie okna
	glutIdleFunc(nextFrame); //Zarejestruj procedurê nextFrame jako procedurê wywo³ywan¹ najczêœciêj jak siê da (animacja)
	glutTimerFunc(1000, timer, 0);

	glutSpecialFunc(specialKeyDown);
	//glutSpecialUpFunc(specialKeyUp);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
}


//Procedura inicjuj¹ca bibliotekê glew
void initGLEW() {
	GLenum err=glewInit();
	if (GLEW_OK!=err) {
		fprintf(stderr,"%s\n",glewGetErrorString(err));
		exit(1);
	}
	
}

void initFonts() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	textRenderer = new TextRenderer(windowWidth, windowHeight);
}

int main(int argc, char** argv) {
	initGLUT(&argc,argv);
	initGLEW();
	initFonts();

	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
	glEnable(GL_DEPTH_TEST);
	glEnable
		(
		GL_LIGHTING
		);
	glEnable
		(GL_LIGHT4);

	map = new Map();
	glutMainLoop();
	
	delete shaderProgram;
	return 0;
}
