#include <vector>
#include <iostream>
#include <SDL_image.h>
#include "grid.h"
#include "tile.h"
#include "window.h"

Grid::Grid(int i_length, Window* o_Window) : GameObject(o_Window, this)
{
	std::vector<int> v_ScreenSize = o_Window->GetScreenSize();
	this->o_Window = o_Window;
	i_gridSize;
	i_posX;
	i_posY;
	if (v_ScreenSize[0]<v_ScreenSize[1])
	{
		i_gridSize = v_ScreenSize[0];
		i_posX = 0;
		i_posY = (v_ScreenSize[1] - v_ScreenSize[0]) / 2;
	}
	else if (v_ScreenSize[0] > v_ScreenSize[1])
	{
		i_gridSize = v_ScreenSize[1];
		i_posX = (v_ScreenSize[0] - v_ScreenSize[1]) / 2;
		i_posY = 0;
	}
	else
	{
		i_gridSize = v_ScreenSize[0];
		i_posX = 0;
		i_posY = 0;
	}
	
	InitInfo(i_posX, i_posY, i_gridSize, i_gridSize);
	this->i_length = i_length;
	v_Tiles.resize(i_length * i_length);

	for (int i = 0; i < i_length * i_length; i++)
	{
		v_Tiles[i] = new Tile(i_length, o_Window, this, i, i_gridSize, i_posX, i_posY);
	}

}

void Grid::LoadTexture(Window* o_Window)
{
	SDL_Surface* tmp_image;
	SDL_Texture* tmp_texture;

	tmp_image = IMG_Load("src/0.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/2.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/4.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/8.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/16.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/32.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/64.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/128.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/256.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/512.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/1024.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	tmp_image = IMG_Load("src/2048.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);
	v_Textures.push_back(tmp_texture);

	SDL_FreeSurface(tmp_image);
	SDL_DestroyTexture(tmp_texture);

}

void Grid::Draw()
{
	SDL_Surface* tmp_image;
	SDL_Texture* tmp_texture;

	tmp_image = IMG_Load("src/background.jpg");
	tmp_texture = SDL_CreateTextureFromSurface(o_Window->GetRenderer(), tmp_image);

	SDL_QueryTexture(tmp_texture,NULL, NULL, NULL, NULL);
	SDL_RenderCopy(o_Window->GetRenderer(), tmp_texture, NULL, &o_Rect);

	SDL_FreeSurface(tmp_image);
	SDL_DestroyTexture(tmp_texture);
}

void Grid::SpawnTile()
{
	v_EmptyTiles.clear();

	for (int i = 0; i < i_length * i_length; i++)
	{
		if (v_Tiles[i]->i_value == 0)
		{
			v_EmptyTiles.push_back(i);
		}
	}

	int i_RandomNb = rand() % v_EmptyTiles.size();

	int i_RandomValue = rand() % 4 + 1;

	if (i_RandomValue == 1 || i_RandomValue == 2 || i_RandomValue == 3)
	{
		v_Tiles[v_EmptyTiles[i_RandomNb]]->i_value = 2;
	}
	else
	{
		v_Tiles[v_EmptyTiles[i_RandomNb]]->i_value = 4;
	}

}

int Grid::Get1DCoordFrom2D(int i, int j)
{
	int n = (i * i_length) + j;
	return n;
}

bool Grid::IsInGrid(int i, int j)
{
	if (i >= 0 && i < i_length && j >= 0 && j < i_length)
		return true;
	else
		return false;
}


void Grid::Translation_Left()
{
	//Fusion
	for (int i = 0; i < i_length; i++)
	{
		for (int j = 0; j < i_length; j++)
		{
			if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == 0)
				continue;

			for (int k = 1; k < i_length - j; k++)
			{
				if (v_Tiles[Get1DCoordFrom2D(i, j + k)]->i_value == v_Tiles[Get1DCoordFrom2D(i, j)]->i_value)
				{
					v_Tiles[Get1DCoordFrom2D(i, j)]->i_value += v_Tiles[Get1DCoordFrom2D(i, j + k)]->i_value;
					v_Tiles[Get1DCoordFrom2D(i, j + k)]->i_value = 0;
					break;

				}
				else if (v_Tiles[Get1DCoordFrom2D(i, j + k)]->i_value != 0)
				{
					break;
				}
			}

		}
	}

	//Translation
	for (int i = 0; i < i_length; i++)
	{
		for (int j = 0; j < i_length; j++)
		{
			if ((v_Tiles[Get1DCoordFrom2D(i, j)]->i_value != 0))
				continue;

			int i_TileToSwap = -1;

			for (int k = 1; k < i_length - j; k++)
			{
				if (v_Tiles[Get1DCoordFrom2D(i, j + k)]->i_value != 0)
				{
					i_TileToSwap = Get1DCoordFrom2D(i, j + k);
					break;
				}
			}

			if (i_TileToSwap == -1)
				continue;

			Tile* o_tmpTile = v_Tiles[Get1DCoordFrom2D(i, j)];
			v_Tiles[Get1DCoordFrom2D(i, j)] = v_Tiles[i_TileToSwap];
			v_Tiles[i_TileToSwap] = o_tmpTile;

			int o_tmpGameObj_X = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.x;
			int o_tmpGameObj_Y = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.y;

			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.x = o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.x;
			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.y = o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.y;
			o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.x = o_tmpGameObj_X;
			o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.y = o_tmpGameObj_Y;

			GameObject* o_tmpGameObj = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)];
			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)] = o_Window->v_GameObject_List[i_TileToSwap];
			o_Window->v_GameObject_List[i_TileToSwap] = o_tmpGameObj;

		}
	}
}

void Grid::Translation_Right()
{
	//Fusion
	for (int i = 0; i < i_length; i++)
	{
		for (int j = i_length - 1; j >= 0; --j)
		{
			if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == 0)
				continue;

			for (int k = 1; k <= j; k++)
			{
				if (v_Tiles[Get1DCoordFrom2D(i, j - k)]->i_value == v_Tiles[Get1DCoordFrom2D(i, j)]->i_value)
				{
					v_Tiles[Get1DCoordFrom2D(i, j)]->i_value += v_Tiles[Get1DCoordFrom2D(i, j - k)]->i_value;
					v_Tiles[Get1DCoordFrom2D(i, j - k)]->i_value = 0;
					break;

				}
				else if (v_Tiles[Get1DCoordFrom2D(i, j - k)]->i_value != 0)
				{
					break;
				}
			}

		}
	}

	//Translation
	for (int i = 0; i < i_length; i++)
	{
		for (int j = i_length - 1; j >= 0; --j)
		{
			if ((v_Tiles[Get1DCoordFrom2D(i, j)]->i_value != 0))
				continue;

			int i_TileToSwap = -1;

			for (int k = 1; k <= j; k++)
			{
				if (v_Tiles[Get1DCoordFrom2D(i, j - k)]->i_value != 0)
				{

					i_TileToSwap = Get1DCoordFrom2D(i, j - k);
					break;
				}
			}

			if (i_TileToSwap == -1)
				continue;

			Tile* o_tmpTile = v_Tiles[Get1DCoordFrom2D(i, j)];
			v_Tiles[Get1DCoordFrom2D(i, j)] = v_Tiles[i_TileToSwap];
			v_Tiles[i_TileToSwap] = o_tmpTile;

			int o_tmpGameObj_X = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.x;
			int o_tmpGameObj_Y = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.y;

			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.x = o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.x;
			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.y = o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.y;
			o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.x = o_tmpGameObj_X;
			o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.y = o_tmpGameObj_Y;

			GameObject* o_tmpGameObj = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)];
			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)] = o_Window->v_GameObject_List[i_TileToSwap];
			o_Window->v_GameObject_List[i_TileToSwap] = o_tmpGameObj;
		}
	}
}

void Grid::Translation_Up()
{
	//Fusion
	for (int j = 0; j < i_length; j++)
	{
		for (int i = 0; i < i_length; i++)
		{
			if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == 0)
				continue;

			for (int k = 1; k < i_length - i; k++)
			{
				if (v_Tiles[Get1DCoordFrom2D(i + k, j)]->i_value == v_Tiles[Get1DCoordFrom2D(i, j)]->i_value)
				{
					v_Tiles[Get1DCoordFrom2D(i, j)]->i_value += v_Tiles[Get1DCoordFrom2D(i + k, j)]->i_value;
					v_Tiles[Get1DCoordFrom2D(i + k, j)]->i_value = 0;
					break;

				}
				else if (v_Tiles[Get1DCoordFrom2D(i + k, j)]->i_value != 0)
				{
					break;
				}
			}

		}
	}

	//Translation
	for (int j = 0; j < i_length; j++)
	{
		for (int i = 0; i < i_length; i++)
		{
			if ((v_Tiles[Get1DCoordFrom2D(i, j)]->i_value != 0))
				continue;

			int i_TileToSwap = -1;

			for (int k = 1; k < i_length - i; k++)
			{
				if (v_Tiles[Get1DCoordFrom2D(i + k, j)]->i_value != 0)
				{
					i_TileToSwap = Get1DCoordFrom2D(i + k, j);
					break;
				}
			}

			if (i_TileToSwap == -1)
				continue;

			Tile* o_tmpTile = v_Tiles[Get1DCoordFrom2D(i, j)];
			v_Tiles[Get1DCoordFrom2D(i, j)] = v_Tiles[i_TileToSwap];
			v_Tiles[i_TileToSwap] = o_tmpTile;

			int o_tmpGameObj_X = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.x;
			int o_tmpGameObj_Y = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.y;

			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.x = o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.x;
			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.y = o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.y;
			o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.x = o_tmpGameObj_X;
			o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.y = o_tmpGameObj_Y;

			GameObject* o_tmpGameObj = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)];
			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)] = o_Window->v_GameObject_List[i_TileToSwap];
			o_Window->v_GameObject_List[i_TileToSwap] = o_tmpGameObj;
		}
	}
}

void Grid::Translation_Down()
{
	//Fusion
	for (int j = 0; j < i_length; j++)
	{
		for (int i = i_length - 1; i >= 0; --i)
		{
			if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == 0)
				continue;

			for (int k = 1; k <= i; k++)
			{
				if (v_Tiles[Get1DCoordFrom2D(i - k, j)]->i_value == v_Tiles[Get1DCoordFrom2D(i, j)]->i_value)
				{
					v_Tiles[Get1DCoordFrom2D(i, j)]->i_value += v_Tiles[Get1DCoordFrom2D(i - k, j)]->i_value;
					v_Tiles[Get1DCoordFrom2D(i - k, j)]->i_value = 0;
					break;

				}
				else if (v_Tiles[Get1DCoordFrom2D(i - k, j)]->i_value != 0)
				{
					break;
				}
			}

		}
	}

	//Translation
	for (int j = 0; j < i_length; j++)
	{
		for (int i = i_length - 1; i >= 0; --i)
		{
			if ((v_Tiles[Get1DCoordFrom2D(i, j)]->i_value != 0))
				continue;

			int i_TileToSwap = -1;

			for (int k = 1; k <= i; k++)
			{
				if (v_Tiles[Get1DCoordFrom2D(i - k, j)]->i_value != 0)
				{

					i_TileToSwap = Get1DCoordFrom2D(i - k, j);
					break;
				}
			}

			if (i_TileToSwap == -1)
				continue;

			Tile* o_tmpTile = v_Tiles[Get1DCoordFrom2D(i, j)];
			v_Tiles[Get1DCoordFrom2D(i, j)] = v_Tiles[i_TileToSwap];
			v_Tiles[i_TileToSwap] = o_tmpTile;

			int o_tmpGameObj_X = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.x;
			int o_tmpGameObj_Y = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.y;

			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.x = o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.x;
			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)]->o_Rect.y = o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.y;
			o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.x = o_tmpGameObj_X;
			o_Window->v_GameObject_List[i_TileToSwap]->o_Rect.y = o_tmpGameObj_Y;

			GameObject* o_tmpGameObj = o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)];
			o_Window->v_GameObject_List[Get1DCoordFrom2D(i, j)] = o_Window->v_GameObject_List[i_TileToSwap];
			o_Window->v_GameObject_List[i_TileToSwap] = o_tmpGameObj;
		}
	}
}

bool Grid::LoseCheck()
{
	for (int i = 0; i < i_length; i++)
	{
		for (int j = 0; j < i_length; j++)
		{
			if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == 0)
				return false;

			else if (IsInGrid(i, j + 1) == true)
				if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == v_Tiles[Get1DCoordFrom2D(i, j + 1)]->i_value)
					return false;

			else if (IsInGrid(i, j - 1) == true)
				if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == v_Tiles[Get1DCoordFrom2D(i, j - 1)]->i_value)
					return false;

			else if (IsInGrid(i + 1, j) == true)
				if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == v_Tiles[Get1DCoordFrom2D(i + 1, j)]->i_value)
					return false;

			else if (IsInGrid(i - 1, j) == true)
				if (v_Tiles[Get1DCoordFrom2D(i, j)]->i_value == v_Tiles[Get1DCoordFrom2D(i - 1, j)]->i_value)
					return false;
		}
	}
	return true;

}

bool Grid::WinCheck()
{
	for (int i = 0; i < i_length*i_length; i++)
	{
		if (v_Tiles[i]->i_value == 2048)
			return true;
	}
	return false;
}