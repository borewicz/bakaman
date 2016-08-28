#pragma once

#define MAP_SIZE 4

#include <vector>
#include <array>
#include <fstream>

#include "pacman.h"

enum FieldType
{
	WALL, //0
	PACMAN, //1
	GHOST, //2
	FOOD, //3
	BLANK //4
};

class Map
{
	std::vector<Object*> walls, ghosts, food;
	ShaderProgram *_shaderProgram;
public:
	Map();
	void draw();
	~Map();
	ShaderProgram* shaderProgram() { return _shaderProgram; }
	Pacman *pacman;
};

