#include "ghost.h"

void Ghost::loadMap()
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

void Ghost::setDirection()
{
	int Los;

	Los = rand() % 2;
	// jesli idzie w prawo lub lewo
	if (KierunekX == 1 || KierunekX == -1)
	{
		if (Los)
		{
			KierunekNewZ = 1;
			KierunekNewX = 0;
		}
		else
		{
			KierunekNewZ = -1;
			KierunekNewX = 0;
		}
	}
	// jesli idzie w gore lub dol
	if (KierunekZ == 1 || KierunekZ == -1)
	{
		if (Los)
		{
			KierunekNewX = 1;
			KierunekNewZ = 0;
		}
		else
		{
			KierunekNewX = -1;
			KierunekNewZ = 0;
		}
	}
	// jesli sie zatrzymal
	if (KierunekX == 0 && KierunekZ == 0)
	{
		if (Los)
		{
			if (Los = rand() % 2)
			{
				// lewo
				KierunekX = -1;
				KierunekZ = 0;
				KierunekNewX = -1;
				KierunekNewZ = 0;
			}
			else
			{
				// prawo
				KierunekX = 1;
				KierunekZ = 0;
				KierunekNewX = 1;
				KierunekNewZ = 0;
			}
		}
		else
		{
			if (Los = rand() % 2)
			{
				// gora
				KierunekX = 0;
				KierunekZ = 1;
				KierunekNewX = 0;
				KierunekNewZ = 1;
			}
			else
			{
				// dol
				KierunekX = 0;
				KierunekZ = -1;
				KierunekNewX = 0;
				KierunekNewZ = -1;
			}
		}
	}
}

void Ghost::go()
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
		setDirection();
	}

	/*
	if (Tablica[(int)PozX][(int)PozZ] == JEDZENIE)
	{
	if (Muzyka) PlaySound("data/sfx/jedz.wav", NULL, SND_ASYNC | SND_NOSTOP);
	Tablica[(int)PozX][(int)PozZ] = 0;
	Punkty++;
	IleJedzenia--;
	if (Punkty % 300 == 0) Zycia++;
	if (IleJedzenia == 0) Stan = NextPlansza;
	}

	// jedz bonus
	if (Tablica[(int)PozX][(int)PozZ] == BONUS)
	{
	if (Muzyka) PlaySound("data/sfx/bonus.wav", NULL, SND_ASYNC);
	Tablica[(int)PozX][(int)PozZ] = 0;
	Przezroczysty = true;
	Punkty += 5;
	BonusCzas += 8;
	if (BonusCzas < 9) Bonus(0);
	}
	*/
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