#pragma once

enum Direction
{
	NO_DIRECTION = 0,
	WEST = 1,
	EAST = -1,
	NORTH = 1,
	SOUTH = -1,
};


enum FieldType
{
	WALL, //0
	PACMAN, //1
	GHOST, //2
	FOOD, //3
	BLANK //4
};