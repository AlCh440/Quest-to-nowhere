#include "EnemyController.h"
#include "bat.h"

EnemyController::EnemyController()
{
	name.Create("Enemy");
}

EnemyController::~EnemyController()
{
}

bool EnemyController::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (Enemies[i] != nullptr && Enemies[i]->pendingToDelete == true)
		{
			delete Enemies[i];
			Enemies[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		// skip empty colliders
		if (Enemies[i] == nullptr)
			continue;

		Enemies[i]->PreUpdate();
		
	}

	return true;
}


bool EnemyController::Update(float dt)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		// skip empty colliders
		if (Enemies[i] == nullptr)
			continue;

		Enemies[i]->Update(dt);
	}

	return true;
}

bool EnemyController::PostUpdate()
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		// skip empty colliders
		if (Enemies[i] == nullptr)
			continue;

		Enemies[i]->PostUpdate();

	}
	return true;
}

bool EnemyController::CleanUp()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (Enemies[i] != nullptr)
		{
			delete Enemies[i];
			Enemies[i] = nullptr;
		}
	}

	return true;
}

Enemy* EnemyController::AddEnemy(int x, int y)
{
	Enemy* ret = nullptr;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (Enemies[i] == nullptr)
		{
			ret = Enemies[i] = new Bat(x, y);
			break;
		}
	}

	return ret;
}

void EnemyController::DebugDraw()
{
}
