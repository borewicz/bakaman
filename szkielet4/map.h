#pragma once

#define MAP_SIZE 4

#include <vector>
#include <array>
#include <fstream>

#include "pacman.h"
#include "ghost.h"

class Map
{
	std::vector<Object*> walls, food;
 // , food;
	ShaderProgram *_shaderProgram;
	//int** mapTable;
	std::vector<std::vector<int>> mapTable;
public:
	Map();
	void draw();
	void manage();
	~Map();
	ShaderProgram* shaderProgram() { return _shaderProgram; }
	Pacman *pacman;
	std::vector<Ghost*> ghosts;
	//Object*** getMapTable() { return mapTable; }
};

