#include "pacman.h"

/*
case GLUT_KEY_UP:
Pacman.KierunekNewX = 0;
Pacman.KierunekNewZ = 1;
break;
case GLUT_KEY_RIGHT:
Pacman.KierunekNewX = -1;
Pacman.KierunekNewZ = 0;
break;
case GLUT_KEY_DOWN:
Pacman.KierunekNewX = 0;
Pacman.KierunekNewZ = -1;
break;
case GLUT_KEY_LEFT:
Pacman.KierunekNewX = 1;
Pacman.KierunekNewZ = 0;


*/
void Pacman::loadMap()
{
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

	Tablica.resize(boardSizeRow, std::vector<int>(boardSizeCol, 0));

	for (int row = 0; row < boardSizeRow; row++)
		for (int col = 0; col < boardSizeCol; col++)
			inputFile >> Tablica[row][col];
}

void Pacman::goLeft()
{
	//setX(x() - 0.1f);
	KierunekNewX = -1;
	KierunekNewZ = 0;
}

void Pacman::goDown()
{
	//setY(y() - 0.1f);
	KierunekNewX = 0;
	KierunekNewZ = -1;
}

void Pacman::goUp()
{
	KierunekNewX = 0;
	KierunekNewZ = 1;
	//setY(y() + 0.1f);
}

void Pacman::goRight()
{
	KierunekNewX = 1;
	KierunekNewZ = 0;
	//setX(x() + 0.1f);
}

void Pacman::go()
{
	if (!_start) return;
	float Przesow = 0.17;

	//Przesow = Opoznienie * Predkosc;
	//if (Przesow > 0.4) Przesow = 0.4; //gdy wyciaga malo klatek

	PozNewX = PozX + (float)KierunekX * Przesow;
	PozNewZ = PozZ + (float)KierunekZ * Przesow;

	//printf("%d, %d\n", (int)(PozNewX / 2), (int)(PozNewZ / 2));
	// jesli zatrzymany
	if (KierunekX == 0 && KierunekZ == 0)
	{
		KierunekX = KierunekNewX;
		KierunekZ = KierunekNewZ;
	}
	// ******************* idzie w gore **********************
	if (KierunekZ == 1)
	{
		// *************** chce skrecic w lewo
		if (KierunekNewX == -1)
		{
			// nie ma sciany
			//if (Tablica[(int)(PozNewX + 0.5)][(int)PozNewZ] != FieldType::WALL)
			if (getItemFromMap(PozNewX - 2, PozNewZ) != FieldType::WALL)
			{
				// moge juz skrecic w lewo
				//if (PozNewZ >= ((int)PozNewZ)) // + 0.5))
				{
					PozX = PozNewX;
					PozZ = (int)PozNewZ; // +0.5;
					if ((int)PozZ % 2 == 1)
						PozZ += KierunekNewX;
					KierunekX = 1;
					KierunekZ = 0;
				}
			}
			else
				KierunekNewX = 0;
		}
		else
			// *************** chce skrecic w prawo
			if (KierunekNewX == 1)
			{
				// nie ma sciany
				//if (Tablica[(int)(PozNewX - 0.6)][(int)PozNewZ] != FieldType::WALL)
				if (getItemFromMap(PozNewX + 2, PozNewZ) != FieldType::WALL)
				{
					// moge juz skrecic w prawo
					//if (PozNewZ >= ((int)PozNewZ)) // + 0.5))
					{
						PozX = PozNewX;
						PozZ = (int)PozNewZ; // +0.5;
						if ((int)PozZ % 2 == 1)
							PozZ += KierunekNewX;
						KierunekX = -1;
						KierunekZ = 0;
					}
				}
				else
					KierunekNewX = 0;
			}
			else
				// *************** chce skrecic w dol
				if (KierunekNewZ == -1)
				{
					KierunekZ = -1;
				}
		// *************** nie chce skrecac
		// brak przeszkody
		if (KierunekZ == 1)
		{
			//if (Tablica[(int)PozNewX][(int)(PozNewZ + 0.5)] != FieldType::WALL)
			if (getItemFromMap(PozNewX, PozNewZ + 2) != FieldType::WALL)
			{
				Obrot = 180;
				PozZ = PozNewZ;
			}
			// jest przeszkoda
			else
			{
				KierunekX = 0;
				KierunekZ = 0;
				PozZ = (int)PozNewZ; // +0.5;
			}
		}
	}


	// ******************* idzie w dol **********************
	if (KierunekZ == -1)
	{
		// *************** chce skrecic w lewo
		if (KierunekNewX == -1)
		{
			// nie ma sciany
			//if (Tablica[(int)(PozNewX + 0.5)][(int)PozNewZ] != FieldType::WALL)
			if (getItemFromMap(PozNewX - 2, PozNewZ) != FieldType::WALL)
			{
				// moge juz skrecic w lewo
				//if (PozNewZ <= ((int)PozNewZ)) // + 0.5))
				{
					PozX = PozNewX;
					PozZ = (int)PozNewZ; // +0.5;
					if ((int)PozZ % 2 == 1)
						PozZ += KierunekNewX;
					KierunekX = 1;
					KierunekZ = 0;
				}
			}
			else
				KierunekNewX = 0;
		}
		else
			// *************** chce skrecic w prawo
			if (KierunekNewX == 1)
			{
				// nie ma sciany

				//if (Tablica[(int)(PozNewX - 0.6)][(int)PozNewZ] != FieldType::WALL)
				if (getItemFromMap(PozNewX + 2, PozNewZ) != FieldType::WALL)
				{
					// moge juz skrecic w prawo
					//if (PozNewZ <= ((int)PozNewZ)) // + 0.5))
					{
						PozX = PozNewX;
						PozZ = (int)PozNewZ; // +0.5;
						if ((int)PozZ % 2 == 1)
							PozZ += KierunekNewX;
						KierunekX = -1;
						KierunekZ = 0;
					}
				}
				else
					KierunekNewX = 0;
			}
			else
				// *************** chce skrecic w gore
				if (KierunekNewZ == 1)
				{
					KierunekZ = 1;
				}
		// *************** nie chce skrecac
		if (KierunekZ == -1)
		{
			// brak przeszkody
			//if (Tablica[(int)PozNewX][(int)(PozNewZ - 0.6)] != FieldType::WALL)
			if (getItemFromMap(PozNewX, PozNewZ - 1) != FieldType::WALL)
			{
				Obrot = 0;
				PozZ = PozNewZ;
			}
			// jest przeszkoda
			else
			{
				KierunekX = 0;
				KierunekZ = 0;
				PozZ = (int)PozNewZ; // +0.5;
			}
		}
	}

	// ******************* idzie w PRAWO **********************
	if (KierunekX == 1)
	{
		if (KierunekNewZ == 1)
		{
			if ((getItemFromMap(PozNewX, PozNewZ + 2) != FieldType::WALL))
				// && (PozNewX >= (int)PozNewX) && (PozNewX < (int)PozNewX + 0.9))
			{
				PozX = (int)PozNewX;// +0.5;
				if ((int)PozX % 2 == 1)
					PozX -= KierunekNewZ;
				PozZ = PozNewZ;
				KierunekX = 0;
				KierunekZ = 1;
			}
			else
				KierunekNewZ = 0;
		}
		else if (KierunekNewZ == -1)
		{
			if ((getItemFromMap(PozNewX, PozNewZ - 2) != FieldType::WALL))
				//&& (PozNewX >= (int)PozNewX) && (PozNewX < (int)PozNewX + 0.9))
			{
				PozX = (int)PozNewX;
				if ((int)PozX % 2 == 1)
					PozX += KierunekNewZ;
				PozZ = PozNewZ;
				KierunekX = 0;
				KierunekZ = -1;
			}
			else
				KierunekNewZ = 0;
		}
		else if (KierunekNewX == -1)
			KierunekX = -1;
		// *************** nie chce skrecac
		if (KierunekX == 1)
		{
			if (getItemFromMap(PozNewX + 2, PozNewZ) != FieldType::WALL)
			{
				Obrot = -90;
				PozX = PozNewX;
			}
			else
			{
				KierunekX = 0;
				KierunekZ = 0;
				PozX = (int)PozNewX;
			}
		}
	}

	// ******************* idzie w LEWO **********************
	if (KierunekX == -1)
	{
		if (KierunekNewZ == 1)
		{
			if ((getItemFromMap(PozNewX, PozNewZ + 2) != FieldType::WALL))
			//	&& (PozNewX <= ((int)PozNewX))) //&& (PozNewX > (int)PozNewX - 0.1))
			{
				PozX = (int)PozNewX;
				if ((int)PozX % 2 == 1)
					PozX += KierunekNewZ;
				PozZ = PozNewZ;
				KierunekX = 0;
				KierunekZ = 1;
			}
			else
				KierunekNewZ = 0;
		}
		else if (KierunekNewZ == -1)
		{
			if ((getItemFromMap(PozNewX, PozNewZ - 2) != FieldType::WALL))
//				&& (PozNewX <= ((int)PozNewX))) //&& (PozNewX > (int)PozNewX - 0.1))
			{
				PozX = (int)PozNewX; // +0.5;
				PozZ = PozNewZ;
				KierunekX = 0;
				KierunekZ = -1;
			}
			else
				KierunekNewZ = 0;
		}
		else if (KierunekNewX == 1)
			KierunekX = 1;
		// *************** nie chce skrecac
		if (KierunekX == -1)
		{
			if (getItemFromMap(PozNewX - 1, PozNewZ) != FieldType::WALL)
			{
				Obrot = 90;
				PozX = PozNewX;
			}
			else
			{
				KierunekX = 0;
				KierunekZ = 0;
				PozX = (int)PozNewX;
			}
		}
	}

	setX(PozX);
	setY(PozZ);
}