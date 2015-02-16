#pragma once

#include <Game/Creep.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>

class GameScene;

struct CreepData
{
	int health = 0;
	int attack = 0;
	int reward = 0;
	float speed = 0.f;
	int hbWidth = 0;
	int hbHeight = 0;
	Vec2 hbOffset;
	Vec2 offset;
	int idleAnim = -1;
	int moveAnim = -1;
	int attackAnim = -1;
};

class CreepManager
{
private:
	GameScene* scene_ = nullptr;

	std::map<std::string, CreepData> creepDatas_;
	std::vector<Creep*> creeps_;
	std::list<int> spawnQ_;
	
	int spawnCD_ = 0.0f;

	int GetFirstInactive();
	int NewCreep(const std::string& type, int path);

public:
	int spawnDelay_ = 500.f;

	CreepManager(GameScene* scene, int initialNum);
	~CreepManager();

	void LoadCreepData(const std::string& name);

	void QCreep(const std::string& type, int path);
	int QRandom(int path);

	Creep* GetFirstWithin(float range, const Vec2& position);
	Creep* GetColliding(const Rect& hitbox);
	bool AllDead();

	void Update(float delta);
	void FixedUpdate();
	void Draw(float interp);
};

