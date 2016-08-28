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

//typedef std::array<Object, MAP_SIZE> FieldLine;

class Map
{
	//std::array<int, 4> field = std::array<int, 4> { { 0, 0, 0, 0 }, { 0, 4, 4, 0 }, { 0, 4, 4, 0 }, { 0, 0, 0, 0 } };
	//std::array<FieldLine, MAP_SIZE> map;
	std::vector<Object*> walls, ghosts, food;
	ShaderProgram *_shaderProgram;
	//glm::mat4 _modelMatrix;
public:
	Map(glm::mat4 *modelMatrix);
	Map();
	void draw();
	~Map();
	ShaderProgram* shaderProgram() { return _shaderProgram; }
	Pacman *pacman;
	//glm::mat4* modelMatrix() { return _modelMatrix;  }
	//void setModelMatrix(glm::mat4 *modelMatrix) { _modelMatrix = modelMatrix;
	//for (auto o : walls)}
	//TMP
	//Object* pacman;
};

