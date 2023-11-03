#pragma once

#include <SDL.h>
#include <vector>

class GameObject;

class Window
{
private:
	SDL_Window* o_SDLWindow;
	SDL_Renderer* o_SDLRenderer;

	int i_width;
	int i_height;

public:

	std::vector<GameObject*> v_GameObject_List;

	Window(int i_width, int i_height);

	SDL_Renderer* GetRenderer();

	std::vector<int> GetScreenSize();

	void AddGameObj(GameObject* o_GameObj);

	void DeleteGameObj();

	void DrawAllGameObj();

	~Window();

};