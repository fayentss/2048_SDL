#pragma once
#include <SDL.h>

class Window;
class Grid;

class GameObject
{
protected:

	SDL_Renderer* o_SDLRenderer;
	
	Grid* o_Grid;

public:
	SDL_Rect o_Rect;

	GameObject(Window* o_window, Grid* o_Grid);

	void InitInfo(int i_posX, int i_posY, int i_width, int i_height);

	virtual void Draw();
};