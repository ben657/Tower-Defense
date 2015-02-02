#pragma once

#include <Game/Tower.h>
#include <vector>
#include <map>

class GameScene;

struct TowerData
{
	int health = 0;
	int attack = 0;
	float attackDelay = 0.f;
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
	TowerManager(GameScene* scene, int initialNum);
	~TowerManager();

	void NewCreep(const std::string& type, const Vec2& position);

	void Update(float delta);
	void FixedUpdate();
	void Draw();
};

