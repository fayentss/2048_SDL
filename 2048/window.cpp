#include <iostream>
#include <SDL.h>
#include "window.h"
#include "game_object.h"

Window::Window(int i_width, int i_height)
{
	o_SDLWindow = NULL;
	o_SDLRenderer = NULL;

	this->i_width = i_width;
	this->i_height = i_height;

	//Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		exit(1);
	}

	//Create window
	if (SDL_CreateWindowAndRenderer(i_width, i_height, 0, &o_SDLWindow, &o_SDLRenderer) == -1)
	{
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		exit(1);
	}

}

SDL_Renderer* Window::GetRenderer()
{
	return o_SDLRenderer;
}

std::vector<int> Window::GetScreenSize()
{
	std::vector<int> v_ScreenSize;

	v_ScreenSize.push_back(i_width);
	v_ScreenSize.push_back(i_height);

	return v_ScreenSize;
}

void Window::AddGameObj(GameObject* o_GameObj)
{
	v_GameObject_List.push_back(o_GameObj);
}

void Window::DrawAllGameObj()
{
	SDL_RenderClear(o_SDLRenderer);

	for (int i = 0; i < v_GameObject_List.size(); i++)
	{
		v_GameObject_List[i]->Draw();
	}
	
	SDL_RenderPresent(o_SDLRenderer);

}

Window::~Window()
{
	// Destroy the window. This will also destroy the surface
	SDL_DestroyWindow(o_SDLWindow);

	// Quit SDL
	SDL_Quit();

	exit(1);
}