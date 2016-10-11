#include "map.h"


Map::Map()
{
	_shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
	std::ifstream inputFile(".\\main.map");
	if (!inputFile)
	{
		printf("Cannot find map file %s", "main.map");
		return;
	}
	int boardSizeRow;
	int boardSizeCol;
	//inputFile.open();
	inputFile >> boardSizeRow;
	inputFile >> boardSizeCol;

	/*
	mapTable = new int*[boardSizeCol];
	for (int i = 0; i <boardSizeCol; i++)
		mapTable[i] = new int[boardSizeRow];
		*/

	mapTable.resize(boardSizeCol, std::vector<int>(boardSizeRow, 0));
	Object *obj;
	Ghost *ghost;

	for (int row = 0; row < boardSizeRow; row++)
	{
		for (int col = 0; col < boardSizeCol; col++)
		{
			int fieldType;
			inputFile >> fieldType;
			switch (fieldType)
			{
				case FieldType::WALL:
					obj =  new Object(
						".\\cube.obj",
						"metal.tga",
						_shaderProgram);
					obj->setX(row * 2);
					obj->setY(col * 2);
					//printf("%.2f, %.2f\n", obj->x(), obj->y());
					walls.push_back(obj);
					break;
				case FieldType::PACMAN:
					pacman = new Pacman(_shaderProgram);
					pacman->setX(row * 2);
					pacman->setY(col * 2);
					pacman->start();
					break;
				case FieldType::GHOST:
					ghost = new Ghost(_shaderProgram);
					ghost->setX(row * 2);
					ghost->setY(col * 2);
					ghost->start();
					ghosts.push_back(ghost); 
					break;
				case FieldType::FOOD:
					obj = new Object(
						".\\cube.obj",
						"stones2.tga",
						_shaderProgram);
					obj->setX(row * 2);
					obj->setY(col * 2);
					food.push_back(obj);
					break;
				default:
					break;
			}
		}
	}
}

void Map::draw()
{
	//manage();
	for (auto obj : walls)
		obj->draw();
	for (auto ghost : ghosts)
		ghost->stop();
	for (auto f : food)
		f->draw();
	pacman->draw();
}

void Map::manage()
{
	int i;
	for (i = 0; i < food.size(); i++)
	{
		if (pacman->X() == food.at(i)->X() && pacman->Y() == food.at(i)->Y())
		{
			//tutej dodej jedzenie
			food.erase(food.begin() + i);
			break;
		}
	};
	if (food.empty())
		stop();
	for (i = 0; i < ghosts.size(); i++)
	{
		if (pacman->X() == ghosts.at(i)->X() && pacman->Y() == ghosts.at(i)->Y())
		{
			stop();
		}
	};
}

void Map::stop()
{
	for (auto ghost : ghosts)
		ghost->stop();
	pacman->stop();
}

int Map::getRemainedFood()
{
	return food.size();
}
Map::~Map()
{
}
