#include "pacman.h"

void Pacman::goLeft()
{
	setX(x() - 0.1f);
}

void Pacman::goDown()
{
	setY(y() - 0.1f);
}

void Pacman::goUp()
{
	setY(y() + 0.1f);
}

void Pacman::goRight()
{
	setX(x() + 0.1f);
}