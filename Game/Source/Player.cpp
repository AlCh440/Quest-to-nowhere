#include "App.h"
#include "Player.h"
#include "Module.h"

#include "Render.h"
#include "Textures.h"
#include "Input.h"

Player::Player() : Module()
{
	is_moving = false;

	idle.PushBack({ 0, 0, 14, 19 });
	idle.PushBack({ 0, 44, 14, 19 });
	idle.PushBack({ 0 , 88, 14, 19 });
	idle.PushBack({ 0, 132, 14, 19 });
	
	
	idle.loop = true;
	idle.speed = 0.1f;

	right_running.PushBack({ 17, 0, 19, 20 });
	right_running.PushBack({ 17, 44, 19, 20 });
	right_running.PushBack({ 17, 88, 19, 20 });
	right_running.PushBack({ 17, 132, 19, 20 });
	right_running.PushBack({ 17, 175, 19, 20 }); 
	right_running.PushBack({ 17, 220, 19, 20 });

	right_running.loop = true;
	right_running.speed = 0.1f;

	left_running.PushBack({ 40, 0, 19, 20 });
	left_running.PushBack({ 40, 44, 19, 20 });
	left_running.PushBack({ 40, 88, 19, 20 });
	left_running.PushBack({ 40, 132, 19, 20 });
	left_running.PushBack({ 40, 175, 19, 20 });
	left_running.PushBack({ 40, 220, 19, 20 });

	left_running.loop = true;
	left_running.speed = 0.1f;
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
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		momentum.x += 1;
		is_moving = true;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		momentum.x -= 1;
		is_moving = true;
	}

	return true;
}

// Called each loop iteration
bool Player::Update(float dt)
{
	player.x += momentum.x;

	if (momentum.x < -2) momentum.x = -2;
	else if (momentum.x > 2) momentum.x = 2;

	
	if (momentum.x < 0)
	{
		momentum.x++;
		direction = 2;
	}
	else if (momentum.x > 0)
	{
		momentum.x--;
		direction = 1;
	}
	else if (momentum.x == 0)
	{
		direction = 0;
	}

	if (direction == 0)
	{
		current_animation = &idle;
	}
	else if (direction == 1)
	{
		current_animation = &right_running;
	}
	else if (direction == 2)
	{
		current_animation = &left_running;
	}

	current_animation->Update();
	is_moving = false;
	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{

	//Drawing player
	app->render->DrawTexture(idle_player, player.x, player.y, &current_animation->GetCurrentFrame());

	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
}


