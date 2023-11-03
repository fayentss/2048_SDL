#pragma once
#include "game_object.h"

class Tile : GameObject
{
public:

	int i_value;

	Window* o_Window;

	Grid* o_Grid;

	Tile(int i_length, Window* o_Window, Grid* o_Grid, int i_ID, int i_gridSize, int i_gridPosX, int i_gridPosY);

	void Draw() override;

};