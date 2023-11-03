#pragma once
#include <vector>
#include "tile.h"
#include "game_object.h"

class Grid : GameObject
{
private:

	Window* o_Window;
	int i_gridSize;
	int i_posX;
	int i_posY;

public:

	int i_length;

	std::vector<Tile*> v_Tiles;

	std::vector<int> v_EmptyTiles;

	std::vector<SDL_Texture*> v_Textures;

	Grid(int i_length, Window* o_window);

	void LoadTexture(Window* o_Window);

	void Draw() override;

	void SpawnTile();

	int Get1DCoordFrom2D(int i, int j);

	bool IsInGrid(int i, int j);

	void Translation_Left();

	void Translation_Right();

	void Translation_Up();

	void Translation_Down();

	bool LoseCheck();

	bool WinCheck();

};