#include "App.h"
#include "Player.h"
#include "Module.h"
#include "Scene.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Scene.h"
#include "Collisions.h"

Player::Player() : Module()
{
	name.Create("player");

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

	player = { 32, 250, 19, 19 };

	can_move_left = true;
	can_move_right = true;
	can_move_down = true;
	can_jump = true;
}

Player::~Player()
{}

bool Player::Awake(pugi::xml_node& config)
{
	bool ret = true;

	player.x = config.child("player_").attribute("x").as_int();
	player.y = config.child("player_").attribute("y").as_int();
	max_momentum.x = config.child("max_mom").attribute("x").as_int();
	max_momentum.y = config.child("max_mom").attribute("y").as_int();
	gravity_ = config.child("player_grav").attribute("gravity").as_int();

	return ret;
}
// Load assets
bool Player::Start()
{
	idle_player = app->tex->Load("Assets/Textures/boxer/iddle_sheet.png");

	hit_player = app->coll->AddCollider(player, Collider::Type::PLAYER, app->player);
	near_right = app->coll->AddCollider({ player.x + player.w, player.y, 2, 19 }, Collider::Type::NEAR, app->player);
	near_left = app->coll->AddCollider({ player.x - 1, player.y, 1, 19 }, Collider::Type::NEAR, app->player);
	near_down = app->coll->AddCollider({ player.x, player.y + player.w, 19, 4 }, Collider::Type::NEAR, app->player);


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
	if (!(app->scene->stop_game))
	{
		if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && can_move_right)
		{
			momentum.x += 2;
			is_moving = true;
		}

		if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && can_move_left)
		{
			momentum.x -= 2;
			is_moving = true;
		}

		if ((app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && can_jump)
		{
			momentum.y = -10;
			can_jump = false;
		}
	}
	return true;
}

// Called each loop iteration
bool Player::Update(float dt)
{
	gravity();

	player.x += momentum.x;
	player.y += momentum.y;

	if (momentum.x < -max_momentum.x) momentum.x = -max_momentum.x;
	else if (momentum.x > max_momentum.x) momentum.x = max_momentum.x;
	
	if (momentum.y > max_momentum.y) momentum.y = max_momentum.y;

	
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
	can_move_right = true;
	can_move_left = true;
	can_move_down = true;

	// MOVING COLLITIONS

	hit_player->SetPos(player.x, player.y);
	near_right->SetPos(player.x + player.w, player.y);
	near_left->SetPos(player.x - 1, player.y);
	near_down->SetPos(player.x, player.y + player.h);

	return true;
}

// Called each loop iteration
bool Player::PostUpdate()
{

	//Drawing player
	app->render->DrawTexture(idle_player, player.x, player.y, &current_animation->GetCurrentFrame());

	return true;
}

void Player::gravity()
{
	if (can_move_down)
	{
		momentum.y += gravity_;
	}
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL)
	{
		if (c1 == near_down)
		{
			if (momentum.y > 0)
			{
				if (player.x > c2->rect.x) player.y = c2->rect.y - player.h;
				momentum.y = 0;
			}
			can_jump = true;
			can_move_down = false;
		}
		else if (c1 == near_right)
		{
			if (momentum.x > 0 && player.x < c2->rect.x)
			{
				player.x = c2->rect.x - player.w;
				momentum.x = 0;
			}
			can_move_right = false;
		}
		else if (c1 == near_left)
		{
			if (momentum.x < 0 && player.x > c2->rect.x)
			{
				//player.x = c2->rect.x + c2->rect.w;
				momentum.x = 0;
			}
			can_move_left = false;
		}
	}
	if (c1 == near_down && c2->type == Collider::Type::PLAT)
	{
		if (momentum.y > 0)
		{
			if (player.x + player.h > c2->rect.x) player.y = c2->rect.y - player.h;
			momentum.y = 0;
		}
		can_jump = true;
		can_move_down = false;
	}
}

// Load / Save
bool Player::LoadState(pugi::xml_node& data)
{

	player.x = data.child("player").attribute("x").as_int();
	player.y = data.child("player").attribute("y").as_int();

	return true;
}

bool Player::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node player_ = data.append_child("player");

	player_.append_attribute("x") = player.x;
	player_.append_attribute("y") = player.y;

	return true;
}

void Player::StartLvl()
{
	pugi::xml_document configFile;
	pugi::xml_node config;

	bool ret = false;

	// L01: DONE 3: Load config from XML
	config = app->LoadConfig(configFile);

	player.x = config.child("player").child("player_").attribute("x").as_int();
	player.y = config.child("player").child("player_").attribute("y").as_int();

	app->render->camera.x = config.child("renderer").child("camera").attribute("x").as_int();
	app->render->camera.y = config.child("renderer").child("camera").attribute("y").as_int();

	app->scene->down_cam->SetPos(app->render->camera.x, + 135 -(app->render->camera.y) / 4);
	app->scene->left_cam->SetPos(app->render->camera.x, -(app->render->camera.y) / 4);
	app->scene->right_cam->SetPos(app->render->camera.x + 220, -20 -(app->render->camera.y) / 4);
	app->scene->up_cam->SetPos(app->render->camera.x, - 40 -(app->render->camera.y)/4);
}