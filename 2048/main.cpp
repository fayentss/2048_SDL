#include <iostream>
#include "tile.h"
#include "grid.h"
#include <conio.h>
#include <SDL.h>
#include "window.h"
#include <cmath>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77



void PlayerInput(Grid* o_Grid,Window* o_Window)
{
	bool badKey = true;
	while (badKey)
	{
		badKey = false;
		int i_KeyPressed = 0;
		switch ((i_KeyPressed = _getch()))
		{
		case KEY_UP:
			o_Grid->Translation_Up();
			o_Grid->SpawnTile();
			o_Window->DrawAllGameObj();
			break;
		case KEY_DOWN:
			o_Grid->Translation_Down();
			o_Grid->SpawnTile();
			o_Window->DrawAllGameObj();
			break;
		case KEY_RIGHT:
			o_Grid->Translation_Right();
			o_Grid->SpawnTile();
			o_Window->DrawAllGameObj();
			break;
		case KEY_LEFT:
			o_Grid->Translation_Left();
			o_Grid->SpawnTile();
			o_Window->DrawAllGameObj();
			break;
		default:
			badKey = true;
			break;
		}
	}
}



int main(int argc, char** args)
{
	//srand(time(NULL));

	Window* o_Window = new Window(1000, 1000);

	int i_length = 4;

	Grid* o_Grid = new Grid(i_length, o_Window);

	o_Grid->LoadTexture(o_Window);

	o_Grid->SpawnTile();
	o_Grid->SpawnTile();

	o_Window->DrawAllGameObj();

	bool Game = SDL_TRUE;

	while (Game)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Game = SDL_FALSE;
				break;

			case SDL_KEYUP:
				if (event.key.keysym.sym == 1073741906)
				{
					o_Grid->Translation_Up();
					o_Grid->SpawnTile();
					o_Window->DrawAllGameObj();
				}
				else if (event.key.keysym.sym == 1073741905)
				{
					o_Grid->Translation_Down();
					o_Grid->SpawnTile();
					o_Window->DrawAllGameObj();
				}
				else if (event.key.keysym.sym == 1073741904)
				{
					o_Grid->Translation_Left();
					o_Grid->SpawnTile();
					o_Window->DrawAllGameObj();
				}
				else if (event.key.keysym.sym == 1073741903)
				{
					o_Grid->Translation_Right();
					o_Grid->SpawnTile();
					o_Window->DrawAllGameObj();
				}

			default:
				continue;
			}

		}

		if (o_Grid->LoseCheck() == true)
		{
			std::cout << "vous avez perdu" << std::endl;
			Game = false;
		}
		if (o_Grid->WinCheck() == true)
		{
			std::cout << "vous avez gagné" << std::endl;
			Game = false;
		}

	}
	delete o_Window;

	return 0;

	/////////////////////////////////Matrice de test////////////////////////////////////

	/*
	int i_length = 4;

	Grid* o_Grid = new Grid(i_length);
	
	/////Test fusion separer par nombre

	std::vector<int> v_TestGrid =
	{
		0,0,0,0,
		0,0,0,0,
		2,4,2,0,
		0,0,0,0,
	};

	std::vector<int> v_ExpectedResult =
	{
		0,0,0,0,
		0,0,0,0,
		0,2,4,2,
		0,0,0,0,
	};

	bool error = false;

	for (int i = 0; i < i_length*i_length; i++)
	{
		o_Grid->v_Tiles[i]->i_value = v_TestGrid[i];
	}

	o_Grid->Translation_Right();

	for (int i = 0; i < i_length*i_length; i++)
	{
		if (o_Grid->v_Tiles[i]->i_value != v_ExpectedResult[i])
		{
			std::cout << "Test invalide : la fusion a ete faite" << std::endl;
			error = true;
			break;
		}
	}
	if (error == false)
	{
		std::cout << "Test valide : la fusion n'a pas ete faite (comme prevu)" << std::endl;
	}

	//////lose check test

	v_TestGrid =
	{
		2,4,2,4,
		4,2,4,2,
		2,4,2,4,
		4,2,4,2,
	};

	for (int i = 0; i < i_length * i_length; i++)
	{
		o_Grid->v_Tiles[i]->i_value = v_TestGrid[i];
	}
	
	bool check = o_Grid->LoseCheck();
	if (check == true)
	{
		std::cout << "La lose check fonctionne parfaitement" << std::endl;
	}
	else if (check == false)
	{
		std::cout << "La lose check ne fonctionne pas" << std::endl;
	}
	*/

	

	////////////////////////////////////Gameloop///////////////////////////////////////
	
	/*
	
	bool Game = true;

	int i_length = 4;

	Grid* o_Grid = new Grid(i_length);

	o_Grid->SpawnTile();
	o_Grid->SpawnTile();

	while (Game == true)
	{

		////Affichage
		system("CLS");

		std::cout << std::endl;

		for (int i = 0; i < i_length; i++)
		{
			for (int j = 0; j < i_length; j++)
			{
				if (o_Grid->v_Tiles[i * i_length + j]->i_value == 0)
				{
					std::cout << " | " << "_" << " | ";
				}
				else
				{
					std::cout << " | " << o_Grid->v_Tiles[i * i_length + j]->i_value << " | ";
				}
			};
			std::cout << std::endl << std::endl;
		}

		/////Choix joueur
		PlayerInput(o_Grid);

		if (o_Grid->LoseCheck() == true)
		{
			std::cout << "vous avez perdu" << std::endl;
			Game = false;
		}
		
	}
	*/
	
	
}