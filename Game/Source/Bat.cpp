#include "Bat.h"
#include "Render.h"
#include "Textures.h"
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

    return true;
}

bool Bat::PreUpdate()
{
    return true;
}

bool Bat::Update(float dt)
{
    if (formation.HasFinished()) bat_state = 1;

    if (bat_state == 0) current_animation = &formation;
    else if (bat_state == 1) current_animation = &fly;

    current_animation->Update();

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

void Bat::OnCollision(Collider* c1, Collider* c2)
{
}

bool Bat::LoadState(pugi::xml_node&)
{
    return false;
}

bool Bat::SaveState(pugi::xml_node&) const
{
    return false;
}

bool Bat::CleanUp()
{
    return false;
}

void Bat::StartLvl()
{
}
