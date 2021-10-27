#pragma once
#include "Module.h"
#include "App.h"

#include "SDL/include/SDL.h"

class Player : public Module
{
public:
	Player();
	virtual ~Player();

	bool Start();
	
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();


	bool CleanUp();

private:

	SDL_Texture *idle_player;
};