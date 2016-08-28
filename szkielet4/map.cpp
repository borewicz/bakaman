#include "map.h"


Map::Map(/*glm::mat4 *modelMatrix*/ /* tmp */)
{
	//_modelMatrix = new glm::mat4(0.0f);
	//_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	Object *obj;

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
					walls.push_back(obj);
					break;
				case FieldType::PACMAN:
					pacman = new Pacman(_shaderProgram);
					pacman->setX(row * 2);
					pacman->setY(col * 2);
					break;
				default:
					break;
			}
		}
	}
}

void Map::draw()
{
	for (auto obj : walls)
	{
		obj->draw();
	}
	pacman->draw();
}

Map::~Map()
{
}
