#include "App.h"
#include "Player.h"
#include "Module.h"

#include "Render.h"
#include "Textures.h"

Player::Player() : Module()
{
}

Player::~Player()
{}

// Load assets
bool Player::Start()
{
	idle_player = app->tex->Load("Assets/Textures/boxer/iddle_sheet.png");
				 

	return true;
}

// Unload assets
bool Player::CleanUp()
{


	return true;
}

// Called each loop iteration
bool Player::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Player::Update(float dt)
{


	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{

	//Drawing player
	app->render->DrawTexture(idle_player, 100, 100);

	return true;
}


