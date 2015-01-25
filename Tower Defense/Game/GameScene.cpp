#include "GameScene.h"

#include <Game/Creeps/Bunny.h>

GameScene::GameScene()
{
	HAPI->SetShowFPS(true);

	map = new Map("map1");
	AddEntity(map);

	gfx->LoadTexture("Data/creeps/bunny.png", "bunny");

	Bunny* bunny = new Bunny(100, 50, 0);
	AddEntity(bunny);

	//Temp path data
	//TODO: Load path data from file
	paths_ = new Vec2*[1];
	paths_[0] = new Vec2[2];
}

GameScene::~GameScene()
{

}

bool GameScene::PlaceTurret(const Vec2& position)
{
	if (!map->CanPlace(position))
		return false;

	//Make turret
	return true;
}

void GameScene::Update(float delta)
{
	Scene::Update(delta);

	if (input->MouseBtnJustDown(0))
	{
		HAPI->DebugText(map->CanPlace(input->MousePos()) ? "Can place" : "Cannot place");
	}
}