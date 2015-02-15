#pragma once

#include <Game/Tower.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>

class GameScene;

struct TowerData
{
	int health = 0;
	int attack = 0;
	int cost = 0;
	float range = 0.f;
	float attackDelay = 0.f;
	std::string projType = "";
	int hbWidth = 0;
	int hbHeight = 0;
	Vec2 hbOffset;
	Vec2 offset;
	int idleAnim = -1;
	int fireAnim = -1;
};

class TowerManager
{
private:
	GameScene* scene_ = nullptr;

	std::map<std::string, TowerData> towerDatas_;	
	std::vector<Tower*> towers_;

	Tower* GetFirstInactive();

public:
	std::vector<std::string> towerTypes_;

	TowerManager(GameScene* scene, int initialNum);
	~TowerManager();

	void LoadTowerData(const std::string& name);

	void NewTower(const std::string& type, const Vec2& position);
	int GetCost(const std::string& type){ return towerDatas_[type].cost; };

	void Update(float delta);
	void FixedUpdate();
	void Draw();
};

