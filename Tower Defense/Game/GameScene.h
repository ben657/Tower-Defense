#pragma once

#include <World/Scene.h>
#include <Game/Map.h>
#include <Game/CreepManager.h>
#include <Game/TowerManager.h>
#include <Game/ProjectileManager.h>
#include <UI/Button.h>
#include <Input.h>
#include <fstream>

class GameScene : public Scene
{
private:
	int plMoney = 100;
	int plHealth = 20;

	int numPaths = 0;
	int numCreeps = 0;
	Map* map;
	std::vector<std::vector<Vec2>> paths_;
	std::vector<int> pathLengths_;

	CreepManager* cManager_ = nullptr;
	TowerManager* tManager_ = nullptr;
	ProjectileManager* pManager_ = nullptr;

	Button* towerMenuBtn = nullptr;
	std::vector<Button*> towerBtns;
	std::string placingTower = "";

	int wave = 0;

	float spawnCD = 0.f;
	float mult = 1.0f;

public:
	GameScene(const std::string& mapName);
	~GameScene();

	void SpawnWave();

	void AddMoney(int amount){ plMoney += amount; numCreeps--; }
	void RemHealth(int amount){ plHealth -= amount; }

	CreepManager* GetCM(){ return cManager_; }
	TowerManager* GetTM(){ return tManager_; }
	ProjectileManager* GetPM(){ return pManager_; }

	bool LastPoint(int path, int currentIndex){ return paths_[path].size() - 1 == currentIndex; }
	Vec2 NextPoint(int path, int currentIndex);
	Vec2 GetPoint(int path, int index){ return paths_[path][index]; };

	void Update(float delta) override;
	void FixedUpdate() override;
	void Draw() override;
};