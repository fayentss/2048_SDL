#include <SDL.h>
#include <vector>
#include <iostream>
#include "game_object.h"
#include "window.h"
#include "grid.h"

GameObject::GameObject(Window* o_window, Grid* o_Grid)
{
	this->o_Grid = o_Grid;
	o_SDLRenderer = o_window->GetRenderer();
}

void GameObject::InitInfo(int i_posX, int i_posY, int i_width, int i_height)
{
	o_Rect.x = i_posX;
	o_Rect.y = i_posY;
	o_Rect.w = i_width;
	o_Rect.h = i_height;
}

void GameObject::Draw()
{
}
