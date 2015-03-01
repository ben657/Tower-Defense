#pragma once

#include <World/Scene.h>
#include <Game/Map.h>
#include <Game/CreepManager.h>
#include <Game/TowerManager.h>
#include <Game/ProjectileManager.h>
#include <UI/Button.h>
#include <Input.h>
#include <Audio.h>
#include <fstream>
#include <thread>

class GameScene : public Scene
{
private:
	int plMoney = 0;
	int plHealth = 20;

	int numPaths = 0;
	int numCreeps = 0;
	int wave = 0;

	int towerAnim = 0;

	Map* map_ = nullptr;
	std::vector<std::vector<Vec2>> paths_;
	std::vector<int> pathLengths_;

	CreepManager* cManager_ = nullptr;
	TowerManager* tManager_ = nullptr;
	ProjectileManager* pManager_ = nullptr;

	Button* towerMenuBtn = nullptr;
	std::vector<Button*> towerBtns;
	std::string placingTowerName_ = "";	

	std::thread spawnThread_;

	Entity* placingTower_ = nullptr;

	bool lastSpawning_ = false;
	bool spawning_ = false;

	void StartSpawning();

public:
	GameScene();
	~GameScene();

	void SwitchedTo(const std::string& from) override;
	void SwitchedFrom(const std::string& to) override;

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
	void Draw(float interp) override;
};