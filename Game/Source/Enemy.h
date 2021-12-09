#pragma once

#include "Module.h"
#include "App.h"
#include "Animation.h"

#include "SDL/include/SDL.h"



class Enemy 
{
public:
	

	bool Start();
	bool Awake(pugi::xml_node&);

	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}


	void OnCollision(Collider* c1, Collider* c2);

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	bool CleanUp();

	void StartLvl();

	SDL_Rect player;

	bool pendingToDelete;
private:

	
	int playerframescounter;

}; 
