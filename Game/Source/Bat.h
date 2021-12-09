#pragma once

#include "Enemy.h"
#include "App.h"
#include "Animation.h"

#include "SDL/include/SDL.h"

struct vec2 {
	int x, y;
};

class Bat : public Enemy
{
public:
	Bat(int x, int y);

	virtual ~Bat();
	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void gravity();

	void OnCollision(Collider* c1, Collider* c2);

	// Load / Save
	bool LoadState(pugi::xml_node&) ;
	bool SaveState(pugi::xml_node&) const ;

	bool CleanUp();

	void StartLvl();

	SDL_Rect player;

private:

	SDL_Texture* bat_sprite;
	Animation formation;
	Animation fly;
	Animation death;


	Animation* current_animation;

	int bat_state;
	int direction;
	bool is_moving;

	vec2 position;
	vec2 momentum;
	vec2 max_momentum;

	int gravity_;


	Collider* hit_bat;


};