#include "Bat.h"
#include "Render.h"
#include "Textures.h"
#include "Player.h"
#include "Pathfinding.h"
#include "Map.h"
#include "Collisions.h"
#include "Enemy.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"
#include "App.h"

Bat::Bat(int x, int y)
{
    position.x = x;
    position.y = y;

    Start();
}

Bat::~Bat()
{
}

bool Bat::Start()
{
   bat_sprite = app->tex->Load("Assets/Textures/bat/bat_sprite.png");

    bat_state = 0;
    
    
    formation.PushBack({ 6, 82, 30, 24 });
    formation.PushBack({ 48, 82, 30, 24 });
    formation.PushBack({ 92, 82, 30, 24 });

    formation.loop = false;
    formation.speed = 0.06f;

    fly.PushBack({ 0, 0, 30, 24 });
    fly.PushBack({ 44, 0, 30, 24 });
    fly.PushBack({ 87, 0, 30, 24 });
    fly.PushBack({ 131, 0, 30, 24 });
    fly.PushBack({ 175, 0, 30, 24 });
    fly.PushBack({ 219, 0, 30, 24 });
    fly.PushBack({ 263, 0, 30, 24 });

    fly.loop = true;
    fly.speed = 0.2f;

    hit_bat = app->coll->AddCollider({ position.x, position.y, 30, 24 }, Collider::Type::ENEMY, this, app->scene);

    return true;
}

bool Bat::PreUpdate()
{
    return true;
}

bool Bat::Update(float dt)
{
    iPoint pos = app->map->WorldToMap(position.x, position.y);
    iPoint dest = app->map->WorldToMap(app->player->player.x, app->player->player.y);
    app->pathfinding->CreatePath(pos, dest);

    if (bat_state == 1)
    {
        const DynArray<iPoint>* path = app->pathfinding->GetLastPath();
        if ((path->At(path->Count() - 1)->DistanceManhattan(pos) < 7))
        {
            if (path->At(1) != nullptr)
            {
                if (path->At(1)->x < pos.x)
                {
                    position.x--;
                    direction = 0;
                }
                else if (path->At(1)->x > pos.x)
                {
                    position.x++;
                    direction = 1;
                }

                if (path->At(1)->y < pos.y)
                {
                    position.y--;
                    direction = 2;
                }
                else if (path->At(1)->y > pos.y)
                {
                    position.y++;
                    direction = 3;
                }
            }
        }
    }

    if (formation.HasFinished()) bat_state = 1;

    if (bat_state == 0) current_animation = &formation;
    else if (bat_state == 1) current_animation = &fly;

    current_animation->Update();

    hit_bat->SetPos(position.x, position.y);

    return true;
}

bool Bat::PostUpdate()
{
    app->render->DrawTexture(bat_sprite, position.x, position.y, &current_animation->GetCurrentFrame());
    return true;
}

void Bat::gravity()
{
}


bool Bat::CleanUp()
{
    return false;
}

void Bat::SolveColl()
{
    if (direction == 0) position.x++;
    else if (direction == 1) position.x--;
    else if (direction == 2) position.y++;
    else if (direction == 3) position.y--;
}
