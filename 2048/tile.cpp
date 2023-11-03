#include <iostream>
#include <vector>
#include <cmath>
#include "tile.h"
#include "window.h"
#include "grid.h"



Tile::Tile(int i_length, Window* o_Window, Grid* o_Grid, int i_ID, int i_gridSize, int i_gridPosX, int i_gridPosY) : GameObject(o_Window, o_Grid)
{

	std::vector<int> v_ScreenSize = o_Window->GetScreenSize();
	this->o_Window = o_Window;
	this->o_Grid = o_Grid;
	int i_posX;
	int i_posY;
	float i_offSet;
	int i_tileSize;

	i_offSet = (i_gridSize * 0.05) / (i_length + 1);
	i_tileSize = (i_gridSize - (i_offSet * (i_length + 1))) / i_length;

	i_posX = i_gridPosX + (i_offSet + (i_ID % i_length) * (i_tileSize + i_offSet));
	i_posY = i_gridPosY + (i_offSet + ((i_ID - (i_ID % i_length)) / i_length) * (i_tileSize + i_offSet));
	
	InitInfo(i_posX, i_posY, i_tileSize, i_tileSize);

	i_value = 0;

	o_Window->AddGameObj(this);
}

void Tile::Draw()
{
	if (i_value == 0)
	{
		SDL_QueryTexture(o_Grid->v_Textures[0], NULL, NULL, NULL, NULL);
		SDL_RenderCopy(o_Window->GetRenderer(), o_Grid->v_Textures[0], NULL, &o_Rect);
	}
	else
	{
		int n = log2(i_value);

		SDL_QueryTexture(o_Grid->v_Textures[n], NULL, NULL, NULL, NULL);
		SDL_RenderCopy(o_Window->GetRenderer(), o_Grid->v_Textures[n], NULL, &o_Rect);
	}
}
