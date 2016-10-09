#pragma once

#include "object.h"

class Ghost : public Object
{
	void loadMap();

	float PozNewX;
	float PozNewZ;
	int KierunekX = 0;
	int KierunekZ = 0;
	int Zycia;
	bool Trup;
	float PozX;
	float PozZ;
	int KierunekNewX = 0;
	int KierunekNewZ = 0;
	int Obrot;
	bool _start = false;
	std::vector<std::vector<int>> Tablica;
	int getItemFromMap(float index_1, float index_2) {
		int result;
		//printf("%d, %d\n", (int)(index_1 / 2), (int)(index_2 / 2));
		int x = (int)(index_1 / 2);
		int y = (int)(index_2 / 2);
		//if (x >= 1 && x < 9 && y >= 1 && y < 9)
		return Tablica[x][y];
		//else
		//	return FieldType::WALL;
	}
public:
	Ghost(ShaderProgram *shaderProgram) : Object(".\\cube.obj", "tiger.tga", shaderProgram) {
		loadMap();
	}

	void setDirection();
	void go();
	void start() {
		PozX = x();
		PozZ = y();
		_start = true;
	}
	~Ghost();
};

