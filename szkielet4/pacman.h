#include "object.h"

class Pacman : public Object
{
public:
	Pacman(ShaderProgram *shaderProgram) : Object(".\\cube.obj", "stones.tga", shaderProgram) { }
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
	~Pacman();
};
