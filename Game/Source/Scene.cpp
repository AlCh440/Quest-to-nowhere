#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Collisions.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");

	win_con = false;
	stop_game = false;

}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	app->map->Load("hello.tmx");
	//app->map->Load("iso_nav.tmx");
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	app->coll->AddCollider({ 288, 224, 80, 48 }, Collider::Type::WALL, app->scene);
	app->coll->AddCollider({ 416, 224, 112, 48 }, Collider::Type::WALL, app->scene);

	app->coll->AddCollider({ 560, 224, 96, 96 }, Collider::Type::WALL, app->scene);
	app->coll->AddCollider({ 704, 224, 128, 96 }, Collider::Type::WALL, app->scene);
	app->coll->AddCollider({ 832, 192, 32, 32 }, Collider::Type::WALL, app->scene);
	app->coll->AddCollider({ 864, 64, 16, 128 }, Collider::Type::WALL, app->scene);
	app->coll->AddCollider({ 784, 32, 96, 32 }, Collider::Type::WALL, app->scene);

	app->coll->AddCollider({ 720, 176, 80, 2 }, Collider::Type::PLAT, app->scene);
	app->coll->AddCollider({ 624, 160, 48, 2 }, Collider::Type::PLAT, app->scene);
	app->coll->AddCollider({ 560, 144, 48, 2 }, Collider::Type::PLAT, app->scene);
	app->coll->AddCollider({ 496, 112, 48, 2 }, Collider::Type::PLAT, app->scene);
	app->coll->AddCollider({ 576, 80, 96, 2 }, Collider::Type::PLAT, app->scene);

	app->coll->AddCollider({ 592, 48, 16, 2 }, Collider::Type::PLAT, app->scene);
	app->coll->AddCollider({ 624, 32, 32, 2 }, Collider::Type::PLAT, app->scene);


	app->coll->AddCollider({ 0, 272, 528, 48 }, Collider::Type::WALL, app->scene);

	// WIN / LOSERS
	app->coll->AddCollider({ 528, 272, 32, 32 }, Collider::Type::LOSE, app->scene);
	app->coll->AddCollider({ 656, 272, 48, 32 }, Collider::Type::LOSE, app->scene);

	app->coll->AddCollider({ 816, 0, 32, 32 }, Collider::Type::WIN, app->scene);


	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	

	if (stop_game)
	{
		if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
		{
			//reset player and camera
			app->player->StartLvl();
			
			

			// stop_game
			stop_game = false;
			// win_con
			win_con = false;
			// start_preupdate
			app->start_preupdate = false;
		}
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	
	if (stop_game) stop_input = true;
	else stop_input = false;

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		app->player->StartLvl();

	if ((app->input->GetKey(SDL_SCANCODE_L) || app->input->GetKey(SDL_SCANCODE_F6)) == KEY_DOWN) 
		app->LoadGameRequest();
	
	if ((app->input->GetKey(SDL_SCANCODE_K) || app->input->GetKey(SDL_SCANCODE_F5)) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 5;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 5;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 5;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 5;

	// UPDATING CAM


	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count());

 	app->win->SetTitle(title.GetString());

	if (win_con && stop_game)
	{

		// draw win screen
		app->render->DrawRectangle({ 0, 0, 300, 300 }, 255, 255, 255, 240);

	}
	else if (!win_con && stop_game)
	{

		// draw lose screen
		app->render->DrawRectangle({ 0, 0, 300, 300 }, 0, 0, 0, 240);


	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::OnCollision(Collider* c1, Collider* c2)
{

	if (c1->type == Collider::Type::LOSE)
	{
		stop_game = true;
		win_con = false;
		app->start_preupdate = false;
	}
	else if (c1->type == Collider::Type::WIN)
	{
		stop_game = true;
		win_con = true;
		app->start_preupdate = false;

	}
	else 
	{
		stop_game = false;
	}
}
