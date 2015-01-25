#pragma once

#include <World/Scene.h>
#include <Game/Map.h>
#include <Input.h>

enum TurretType
{

};

class GameScene : public Scene
{
private:
	Map* map;
	Vec2** paths_;

public:
	GameScene();
	~GameScene();

	bool PlaceTurret(const Vec2& position);

	void SpawnCreep();

	Vec2 NextPoint(int path, int currentIndex);

	void Update(float delta) override;
};

