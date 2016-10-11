#include "object.h"

class Pacman : public Object
{
private:
	bool isDead = false;
	Direction currentVerticalDirection, currentHorizontalDirection;
	Direction newVerticalDirection, newHorizontalDirection;
	std::vector<std::vector<int>> Tablica;
	int verticalMovementValue, horizontalMovementValue;

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
	void loadMap();
public:
	Pacman(ShaderProgram *shaderProgram) : Object(".\\cube.obj", "stones.tga", shaderProgram) {
		loadMap();
	}
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
	void go();
	void start() {
		PozX = x();
		PozZ = y(); 
		_start = true;
	}
	void stop() {
		_start = false;
	}
	~Pacman();
};
