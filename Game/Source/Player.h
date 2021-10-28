#pragma once
#include "Module.h"
#include "App.h"
#include "Animation.h"

#include "SDL/include/SDL.h"

struct vec2 {
	int x, y;
};

class Player : public Module
{
public:
	Player();
	virtual ~Player();

	bool Start();
	
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp();

private:

	SDL_Texture *idle_player;
	Animation idle;
	Animation right_running;
	Animation left_running;

	Animation* current_animation;
	int direction;
	bool is_moving;

	SDL_Rect player;
	vec2 momentum;
};