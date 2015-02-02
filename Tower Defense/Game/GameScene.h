#pragma once

#include <World/Scene.h>
#include <Game/Map.h>
#include <Game/CreepManager.h>
#include <Input.h>
#include <fstream>

enum TurretType
{

};

class GameScene : public Scene
{
private:
	Map* map;
	std::vector<std::vector<Vec2>> paths_;
	int* pathLengths_;

	CreepManager* cManager_;

public:
	GameScene();
	~GameScene();

	bool PlaceTurret(const Vec2& position);

	void SpawnCreep();

	Vec2 NextPoint(int path, int currentIndex);
	Vec2 GetPoint(int path, int index){ return paths_[path][index]; };

	void Update(float delta) override;
	void FixedUpdate() override;
	void Draw() override;
};